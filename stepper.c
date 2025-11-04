#include "C:\Users\hp\Desktop\es lab\ti\TivaWare_C_Series-2.2.0.295\inc\tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>

void delayMs(int n);

int main(void)
{
    /* enable clock to GPIOF/B/C at clock gating control register */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;

    /* enable the GPIO pins for the PF2/PF3/PB3/PC4 as output */
    GPIO_PORTF_DIR_R = 0x0C;
    GPIO_PORTB_DIR_R = 0x08;
    GPIO_PORTC_DIR_R = 0x10;

    /* enable the GPIO pins for digital function */
    GPIO_PORTF_DEN_R = 0x0C;
    GPIO_PORTB_DEN_R = 0x08;
    GPIO_PORTC_DEN_R = 0x10;

    while(1)
    {
int cnt=250;
while(cnt>0){
        GPIO_PORTF_DATA_R = 0x04;
        delayMs(10);

        GPIO_PORTF_DATA_R = 0;
        delayMs(10);

        GPIO_PORTF_DATA_R = 0x08;
        delayMs(10);

        GPIO_PORTF_DATA_R = 0;
        delayMs(10);

        GPIO_PORTB_DATA_R = 0x08;
        delayMs(10);

        GPIO_PORTB_DATA_R = 0;
        delayMs(10);

        GPIO_PORTC_DATA_R = 0x10;
        delayMs(10);

        GPIO_PORTC_DATA_R = 0;
        delayMs(10);
cnt--;
}
cnt=100;
while(cnt>0)
    {
        GPIO_PORTC_DATA_R = 0x10;  // PC4 ON
        delayMs(10);

        GPIO_PORTC_DATA_R = 0;     // PC4 OFF
        delayMs(10);

        GPIO_PORTB_DATA_R = 0x08;  // PB3 ON
        delayMs(10);

        GPIO_PORTB_DATA_R = 0;     // PB3 OFF
        delayMs(10);

        GPIO_PORTF_DATA_R = 0x08;  // PF3 ON
        delayMs(10);

        GPIO_PORTF_DATA_R = 0;     // PF3 OFF
        delayMs(10);

        GPIO_PORTF_DATA_R = 0x04;  // PF2 ON
        delayMs(10);

        GPIO_PORTF_DATA_R = 0;     // PF2 OFF
        delayMs(10);
cnt--;
    }
    }
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 4180; j++)
        {
            /* do nothing for 1 ms */
        }
}
