#include <stdint.h>

/*************** RCC ******************/
#define RCC_AHB1ENR     (*(volatile uint32_t *)0x40023830)

/*************** DMA2 *****************/
#define DMA2_LISR       (*(volatile uint32_t *)0x40026400)
#define DMA2_LIFCR      (*(volatile uint32_t *)0x40026408)

#define DMA2_S0CR       (*(volatile uint32_t *)0x40026410)
#define DMA2_S0NDTR     (*(volatile uint32_t *)0x40026414)
#define DMA2_S0PAR      (*(volatile uint32_t *)0x40026418)
#define DMA2_S0M0AR     (*(volatile uint32_t *)0x4002641C)
#define DMA2_S0FCR      (*(volatile uint32_t *)0x40026424)

/************* Arrays *****************/
uint32_t source[5]      = {11, 22, 33, 44, 55};
uint32_t destination[5] = {0};

int main(void)
{
    /* Enable DMA2 Clock */
    RCC_AHB1ENR |= (1<<22);

    /* Disable Stream0 */
    DMA2_S0CR &= ~(1<<0);
    while(DMA2_S0CR & (1<<0));

    /* Clear all Stream0 Flags */
    DMA2_LIFCR = 0x3D;

    /* Source Address */
    DMA2_S0PAR = (uint32_t)source;

    /* Destination Address */
    DMA2_S0M0AR = (uint32_t)destination;

    /* Number of Transfers */
    DMA2_S0NDTR = 5;

    /* Clear Configuration */
    DMA2_S0CR = 0;

    /* Channel 0 */
    DMA2_S0CR &= ~(7<<25);

    /* Memory-to-Memory : DIR[1:0] = 10 at bits [7:6] */
    DMA2_S0CR |= (2<<6);        /* FIX: was (1<<14) which set MSIZE[1] by mistake */

    /* High Priority */
    DMA2_S0CR |= (2<<16);

    /* Peripheral Increment */
    DMA2_S0CR |= (1<<9);//1 different values and 0 same value not address incremented

    /* Memory Increment */
    DMA2_S0CR |= (1<<10);

    /* Peripheral Size = 32-bit */
    DMA2_S0CR |= (2<<11);

    /* Memory Size = 32-bit */
    DMA2_S0CR |= (2<<13);

    /* Direct Mode (FIFO Disabled) */
    DMA2_S0FCR = 0;

    /* Enable Stream */
    DMA2_S0CR |= (1<<0);

    /* Wait for Transfer Complete */
    while(!(DMA2_LISR & (1<<5)));

    while(1);
}
