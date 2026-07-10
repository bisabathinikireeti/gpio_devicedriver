#include <stdint.h>

/************* RCC Registers *************/
#define RCC_CR          (*(volatile uint32_t *)0x40023800)
#define RCC_PLLCFGR     (*(volatile uint32_t *)0x40023804)
#define RCC_CFGR        (*(volatile uint32_t *)0x40023808)
#define RCC_AHB1ENR     (*(volatile uint32_t *)0x40023830)

/************* FLASH Register *************/
#define FLASH_ACR       (*(volatile uint32_t *)0x40023C00)

/************* GPIOB Registers *************/
#define GPIOB_MODER     (*(volatile uint32_t *)0x40020400)
#define GPIOB_ODR       (*(volatile uint32_t *)0x40020414)

void SystemClock_Config(void)
{
    /*-------------------------------------------------
      Enable HSE
    -------------------------------------------------*/
    RCC_CR |= (1 << 16);                // HSEON

    while(!(RCC_CR & (1 << 17)));       // Wait until HSE Ready

    /*-------------------------------------------------
      Configure Flash for 84 MHz
    -------------------------------------------------*/
    FLASH_ACR = 0;

    FLASH_ACR |= (2 << 0);              // 2 Wait States
    FLASH_ACR |= (1 << 8);              // Prefetch Enable
    FLASH_ACR |= (1 << 9);              // Instruction Cache
    FLASH_ACR |= (1 << 10);             // Data Cache

    /*-------------------------------------------------
      Configure PLL

      HSE = 8 MHz
      PLLM = 8
      PLLN = 336
      PLLP = 4
      PLLQ = 7

      SYSCLK = 84 MHz
    -------------------------------------------------*/

    RCC_PLLCFGR = 0;

    RCC_PLLCFGR |= (8 << 0);        // PLLM = 8
    RCC_PLLCFGR |= (336 << 6);      // PLLN = 336
    RCC_PLLCFGR |= (1 << 16);       // PLLP = 4
    RCC_PLLCFGR |= (1 << 22);       // HSE as PLL Source
    RCC_PLLCFGR |= (7 << 24);       // PLLQ = 7

    /*-------------------------------------------------
      Enable PLL
    -------------------------------------------------*/

    RCC_CR |= (1 << 24);                // PLLON

    while(!(RCC_CR & (1 << 25)));       // Wait until PLL Ready

    /*-------------------------------------------------
      Configure Prescalers

      AHB  = /1
      APB1 = /2
      APB2 = /1
    -------------------------------------------------*/

    RCC_CFGR &= ~(0xF << 4);            // HPRE = /1

    RCC_CFGR &= ~(0x7 << 10);
    RCC_CFGR |=  (0x4 << 10);           // APB1 = /2

    RCC_CFGR &= ~(0x7 << 13);           // APB2 = /1

    /*-------------------------------------------------
      Select PLL as System Clock
    -------------------------------------------------*/

    RCC_CFGR &= ~(0x3);

    RCC_CFGR |= (0x2);

    while(((RCC_CFGR >> 2) & 0x3) != 0x2);
}

int main(void)
{
    volatile uint32_t i;

    /* Configure System Clock */
    SystemClock_Config();

    /* Enable GPIOB Clock */
    RCC_AHB1ENR |= (1 << 1);

    /* PB13 Output Mode */
    GPIOB_MODER &= ~(3 << 26);
    GPIOB_MODER |=  (1 << 26);

    while(1)
    {
        GPIOB_ODR ^= (1 << 13);

0        for(i = 0; i < 500000; i++);
    }
}
