#include <stdint.h>

/*
 * DMA2 + ADC1 - Peripheral to Memory Transfer
 * Board  : Raayan Mini STM32F401RBT6
 * Pin    : PC1 = ADC1 Channel 11 (Potentiometer - from User Manual Table 2-8 / Schematic)
 *
 * CORRECTIONS FROM PREVIOUS CODE:
 *   WRONG before : PA0 = ADC1 Channel 0   (not connected to POT on this board)
 *   CORRECT now  : PC1 = ADC1 Channel 11  (POT connected here per schematic)
 *
 *   Changed registers:
 *   1. RCC_AHB1ENR : bit2  = GPIOCEN  (was bit0 = GPIOAEN)
 *   2. GPIOC_MODER : bits[3:2] = 11   (was GPIOA_MODER bits[1:0])
 *   3. ADC1_SMPR1  : SMP11 at bits[5:3] = 111  (was SMPR2 SMP0 at bits[2:0])
 *   4. ADC1_SQR3   : SQ1 = 11         (was SQ1 = 0)
 *
 * ADDRESS REFERENCE (RM0368):
 *   RCC base       = 0x40023800  [Table 1, p.39]
 *   RCC_AHB1ENR    = 0x40023830  [§6.3.9,  p.118]  offset 0x30
 *   RCC_APB2ENR    = 0x40023844  [§6.3.11, p.122]  offset 0x44
 *   GPIOC base     = 0x40020800  [Table 1, p.38]
 *   GPIOC_MODER    = 0x40020800  [§8.4.1,  p.148]  offset 0x00
 *   ADC1 base      = 0x40012000  [Table 1, p.39]
 *   ADC1_SR        = 0x40012000  [§11.12.1, p.229] offset 0x00
 *   ADC1_CR2       = 0x40012008  [§11.12.3, p.232] offset 0x08
 *   ADC1_SMPR1     = 0x4001200C  [§11.12.4, p.234] offset 0x0C  <-- channels 10-18
 *   ADC1_SQR3      = 0x40012034  [§11.12.11,p.237] offset 0x34
 *   ADC1_DR        = 0x4001204C  [§11.12.14,p.239] offset 0x4C
 *   DMA2 base      = 0x40026400  [Table 1, p.39]
 *   DMA2_LISR      = 0x40026400  [§9.5.1,  p.188] offset 0x00
 *   DMA2_LIFCR     = 0x40026408  [§9.5.3,  p.190] offset 0x08
 *   DMA2_S0CR      = 0x40026410  [§9.5.5,  p.191] offset = 0x10 + 0x18*0
 *   DMA2_S0NDTR    = 0x40026414  [§9.5.6,  p.194] offset = 0x14 + 0x18*0
 *   DMA2_S0PAR     = 0x40026418  [§9.5.7,  p.195] offset = 0x18 + 0x18*0
 *   DMA2_S0M0AR    = 0x4002641C  [§9.5.8,  p.195] offset = 0x1C + 0x18*0
 *   DMA2_S0FCR     = 0x40026424  [§9.5.10, p.196] offset = 0x24 + 0x24*0
 *
 * DMA CHANNEL MAPPING [RM Table 29, p.171]:
 *   ADC1 --> DMA2, Stream0, Channel0
 */

/*************** RCC ******************/
#define RCC_AHB1ENR     (*(volatile uint32_t *)0x40023830)
#define RCC_APB2ENR     (*(volatile uint32_t *)0x40023844)

/*************** GPIOC ****************/
#define GPIOC_MODER     (*(volatile uint32_t *)0x40020800)   /* was GPIOA 0x40020000 */

/*************** ADC1 *****************/
#define ADC1_SR         (*(volatile uint32_t *)0x40012000)
#define ADC1_CR2        (*(volatile uint32_t *)0x40012008)
#define ADC1_SMPR1      (*(volatile uint32_t *)0x4001200C)   /* was SMPR2 0x40012010 */
#define ADC1_SQR3       (*(volatile uint32_t *)0x40012034)
#define ADC1_DR         (*(volatile uint32_t *)0x4001204C)

/*************** DMA2 *****************/
#define DMA2_LISR       (*(volatile uint32_t *)0x40026400)
#define DMA2_LIFCR      (*(volatile uint32_t *)0x40026408)

#define DMA2_S0CR       (*(volatile uint32_t *)0x40026410)
#define DMA2_S0NDTR     (*(volatile uint32_t *)0x40026414)
#define DMA2_S0PAR      (*(volatile uint32_t *)0x40026418)
#define DMA2_S0M0AR     (*(volatile uint32_t *)0x4002641C)
#define DMA2_S0FCR      (*(volatile uint32_t *)0x40026424)

/************* Buffer *****************/
#define BUF_LEN   10
uint16_t adc_buf[BUF_LEN] = {0};   /* DMA stores ADC results here */

int main(void)
{
    /* ---------------------------------------------------------------
     * STEP 1: Enable Clocks
     * RCC_AHB1ENR bit2  = GPIOCEN  [RM §6.3.9,  p.118]  <-- CHANGED (was bit0 GPIOAEN)
     * RCC_AHB1ENR bit22 = DMA2EN   [RM §6.3.9,  p.118]
     * RCC_APB2ENR bit8  = ADC1EN   [RM §6.3.11, p.122]
     * --------------------------------------------------------------- */
    RCC_AHB1ENR |= (1<<2);    /* GPIOC clock ON  <-- CHANGED from (1<<0) */
    RCC_AHB1ENR |= (1<<22);   /* DMA2  clock ON */
    RCC_APB2ENR |= (1<<8);    /* ADC1  clock ON */

    /* ---------------------------------------------------------------
     * STEP 2: Configure PC1 as Analog mode
     * GPIOC_MODER bits [3:2] for pin1:  (pin_number * 2)
     *   11 = Analog mode  [RM §8.4.1, p.148]
     * PC1 = ADC1_IN11 per Raayan Mini User Manual Table 2-8
     * <-- CHANGED from GPIOA_MODER bits[1:0] for PA0
     * --------------------------------------------------------------- */
    GPIOC_MODER |= (3<<2);    /* PC1 = Analog mode, bits[3:2] = 11 */

    /* ---------------------------------------------------------------
     * STEP 3: Configure DMA2 Stream0
     * ADC1 --> DMA2 Stream0 Channel0  [RM Table 29, p.171]
     * --------------------------------------------------------------- */

    /* Disable Stream0 first */
    DMA2_S0CR &= ~(1<<0);
    while(DMA2_S0CR & (1<<0));

    /* Clear all Stream0 flags
     * TCIF0=bit5, HTIF0=bit4, TEIF0=bit3, DMEIF0=bit2, FEIF0=bit0
     * Mask = 0x3D  [RM §9.5.3, p.190] */
    DMA2_LIFCR = 0x3D;

    /* Peripheral Address = ADC1_DR (fixed, never changes) [RM §9.5.7] */
    DMA2_S0PAR = (uint32_t)&ADC1_DR;

    /* Memory Address = our adc_buf array [RM §9.5.8] */
    DMA2_S0M0AR = (uint32_t)adc_buf;

    /* Number of transfers = 10 [RM §9.5.6] */
    DMA2_S0NDTR = BUF_LEN;

    /* Clear Configuration register */
    DMA2_S0CR = 0;

    /* Channel 0: CHSEL[2:0] at bits[27:25] = 000 [RM §9.5.5, p.193] */
    DMA2_S0CR &= ~(7<<25);

    /* Direction: Peripheral-to-Memory, DIR[1:0] = 00 at bits[7:6] */
    DMA2_S0CR &= ~(3<<6);

    /* Circular mode ON: CIRC bit8 = 1 [RM §9.3.8, p.176] */
    DMA2_S0CR |= (1<<8);

    /* Medium Priority: PL[1:0] = 01 at bits[17:16] */
    DMA2_S0CR |= (1<<16);

    /* Peripheral Size = 16-bit: PSIZE[1:0] = 01 at bits[12:11] */
    DMA2_S0CR |= (1<<11);

    /* Memory Size = 16-bit: MSIZE[1:0] = 01 at bits[14:13] */
    DMA2_S0CR |= (1<<13);

    /* Peripheral Increment OFF: PINC bit9 = 0 (ADC_DR always same address) */
    DMA2_S0CR &= ~(1<<9);

    /* Memory Increment ON: MINC bit10 = 1 (step through adc_buf[]) */
    DMA2_S0CR |= (1<<10);

    /* Direct Mode: FIFO disabled [RM §9.5.10, p.196] */
    DMA2_S0FCR = 0;

    /* Enable DMA2 Stream0 */
    DMA2_S0CR |= (1<<0);

    /* ---------------------------------------------------------------
     * STEP 4: Configure ADC1 for Channel 11 (PC1)
     * --------------------------------------------------------------- */

    /* Sample time for Channel 11 in SMPR1:
     * SMP11[2:0] at bits[5:3]  (formula: (channel-10)*3 = 1*3 = 3)
     * 111 = 480 cycles  [RM §11.12.4, p.234]
     * <-- CHANGED: was SMPR2 bits[2:0] for channel 0 */
    ADC1_SMPR1 |= (7<<3);

    /* Sequence: 1 conversion, Channel 11 first
     * SQ1[4:0] at bits[4:0] of SQR3 = 11 (channel 11)
     * <-- CHANGED: was (0<<0) for channel 0  [RM §11.12.11, p.237] */
    ADC1_SQR3 |= (11<<0);

    /* ADC CR2:
     * DMA  bit8 = 1 : DMA mode ON         [RM §11.12.3, p.233]
     * DDS  bit9 = 1 : continuous DMA requests
     * CONT bit1 = 1 : continuous conversion
     * ADON bit0 = 1 : ADC ON              [RM §11.12.3, p.234] */
    ADC1_CR2 |= (1<<8);    /* DMA enable */
    ADC1_CR2 |= (1<<9);    /* DDS: keep DMA requests going */
    ADC1_CR2 |= (1<<1);    /* CONT: continuous mode */
    ADC1_CR2 |= (1<<0);    /* ADON: ADC ON */

    /* ---------------------------------------------------------------
     * STEP 5: Start Conversion
     * SWSTART bit30 = 1  [RM §11.12.3, p.232]
     * --------------------------------------------------------------- */
    ADC1_CR2 |= (1<<30);

    /* ---------------------------------------------------------------
     * STEP 6: Wait for first buffer fill complete
     * TCIF0 = bit5 of LISR  [RM §9.5.1, p.188]
     * adc_buf[0..9] = 10 x 12-bit POT readings from PC1
     * Value: 0 (0V) to 4095 (3.3V)
     * --------------------------------------------------------------- */
    while(!(DMA2_LISR & (1<<5)));

    /* Clear TC flag */
    DMA2_LIFCR = (1<<5);

    /* Circular mode keeps running - adc_buf[] always has latest values */

    while(1);
}
