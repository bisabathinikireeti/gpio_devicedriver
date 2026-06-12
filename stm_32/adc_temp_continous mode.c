#include <stdio.h>

#define RCC_AHB1ENR   *((volatile int *)0x40023830)
#define RCC_APB2ENR   *((volatile int *)0x40023844)

#define GPIOC_MODER   *((volatile int *)0x40020800)

#define ADC_SR        *((volatile int *)0x40012000)
#define ADC_CR1       *((volatile int *)0x40012004)
#define ADC_CR2       *((volatile int *)0x40012008)
#define ADC_SMPR1     *((volatile int *)0x4001200C)
#define ADC_SQR3      *((volatile int *)0x40012034)
#define ADC_DR        *((volatile int *)0x4001204C)

volatile int ADC_Value = 0;
float voltage = 0;

void GPIO_PORTC_Init(void);
void ADC1_Init(void);
void ADC1_Read(void);

void GPIO_PORTC_Init(void)
{
    /* Enable GPIOC Clock */
    RCC_AHB1ENR |= (1 << 2);

    while(!(RCC_AHB1ENR & (1 << 2)));

    /* PC0 -> Analog Mode */
    GPIOC_MODER &= ~(0x3 << 0);
    GPIOC_MODER |=  (0x3 << 0);
}

void ADC1_Init(void)
{
    /* Enable ADC1 Clock */
    RCC_APB2ENR |= (1 << 8);

    while(!(RCC_APB2ENR & (1 << 8)));

    /* Channel 10 Sample Time = 480 Cycles */
    ADC_SMPR1 |= (0x7 << 0);

    /* Regular Sequence Rank1 = Channel 10 */
    ADC_SQR3 = 10;

    /* 12-bit Resolution */
    ADC_CR1 &= ~(0x3 << 24);

    /* EOC after each conversion */
    ADC_CR2 |= (1 << 10);

    /* Continuous Conversion Mode */
    ADC_CR2 |= (1 << 1);

    /* ADC ON */
    ADC_CR2 |= (1 << 0);
}

void ADC1_Read(void)
{
    while(!(ADC_SR & (1 << 1)));     // Wait for EOC

    ADC_Value = ADC_DR;              // Read ADC Result

    voltage = (ADC_Value * 3.3f) / 4095.0f;
}

int main(void)
{
    GPIO_PORTC_Init();

    ADC1_Init();

    /* Start Conversion Once */
    ADC_CR2 |= (1 << 30);

    while(1)
    {
        ADC1_Read();

        /* Watch ADC_Value and voltage in debugger */
    }
}
