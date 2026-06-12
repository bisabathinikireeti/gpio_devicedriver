#define RCC_AHB1ENR   *((volatile int *)0x40023830)
#define RCC_APB2ENR   *((volatile int *)0x40023844)

#define GPIO_MODER    *((volatile int *)0x40020800)

#define ADC_SR        *((volatile int *)0x40012000)
#define ADC_CR1       *((volatile int *)0x40012004)
#define ADC_CR2       *((volatile int *)0x40012008)
#define ADC_SMPR1     *((volatile int *)0x4001200C)
#define ADC_SQR3      *((volatile int *)0x40012034)
#define ADC_DR        *((volatile int *)0x4001204C)

#define ADC_CCR       *((volatile int *)0x40012304)

volatile int Temp_value = 0;
float Temperature, voltage;

void GPIO_PORTC_Init(void);
void km_ADC_Init(void);
void km_ADC_Read(void);
void km_Delay(int n);

void GPIO_PORTC_Init(void)
{
    RCC_AHB1ENR |= 0x04;                  // Enable clock for Port C

    while(!(RCC_AHB1ENR & 0x04));         // Wait until Port C clock is enabled

    GPIO_MODER &= ~(0x3);                // Clear PC0 mode bits

    GPIO_MODER |= (0x3);                 // Set PC0 to Analog Mode
}

void km_ADC_Init(void)
{
    RCC_APB2ENR |= (0x1 << 8);           // Enable ADC1 clock

    while(!(RCC_APB2ENR & (0x1 << 8)));  // Wait until ADC clock is enabled

    ADC_SMPR1 |= 0x07;                   // Sample time = 480 cycles

    ADC_SQR3 |= 0x0A;                    // Channel 10 as first regular conversion

    ADC_CR1 &= ~(0x3 << 24);             // 12-bit resolution

    ADC_CR2 |= (0x1 << 10);              // EOCS = 1

    ADC_CR2 |= 0x1;                      // ADON = 1 (Enable ADC)

    ADC_CCR |= (0x1 << 23);              // Enable temperature sensor/VREFINT
}

void km_Delay(int n)
{
    volatile int i = 0;

    for(i = 0; i < (1600 * n); i++)
    {
        ;
    }
}

void km_ADC_Read(void)
{
    ADC_CR2 |= (0x1 << 30);              // Start conversion

    while(!(ADC_SR & 0x02));             // Wait for EOC

    Temp_value = ADC_DR;                 // Read ADC result

    voltage = (Temp_value * 3.3) / 4095.0;

    Temperature = ((voltage - 0.76) / 0.0025) + 25;

    ADC_CR2 &= ~(0x1 << 30);             // Clear SWSTART

    km_Delay(500);                       // Delay 500 ms
}

int main(void)
{
    GPIO_PORTC_Init();

    km_ADC_Init();

    while(1)
    {
        km_ADC_Read();
    }
}
