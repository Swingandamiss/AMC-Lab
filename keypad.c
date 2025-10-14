#include <stdint.h>
#include <stdbool.h>
#include "inc\tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define LCD_clear()   LCD_command(0x1)        /* Clear display LCD */
#define LCD_origin()  LCD_command(0x2)        /* Set to origin LCD */
#define LCD_row1()    LCD_command(0x80)        /* Begin at Line 1 */
#define LCD_row2()    LCD_command(0xC0)  /* Begin at Line 2 */
void shift_out1(unsigned char str);
void LCD_enable(void);
void LCD_command(unsigned char command);
void LCD_putc(unsigned char ascii);
void LCD_puts(unsigned char *lcd_string);
void LCD_init(void);
unsigned char key_scan(unsigned int volatile rec_val);//stores key pressed
int main(void)
{
uint32_t ui32ADC0Value;
unsigned char Dig_val;//values for LCD
volatile uint32_t ui32TempAvg,Temp_val;



SYSCTL_RCGCGPIO_R |= 0x039;   /* enable clock to GPIOD/E/A/F */
  SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
   
    /* initialize PE3 for AIN4 input  */
    GPIO_PORTD_AFSEL_R |= 8;       /* enable alternate function */
    GPIO_PORTD_DEN_R &= ~8;        /* disable digital function */
    GPIO_PORTD_AMSEL_R |= 8;       /* enable analog function */
GPIO_PORTE_DIR_R |= 0x0C; /*   */
GPIO_PORTE_DEN_R |= 0x0C;
GPIO_PORTA_DIR_R |= 0x20;
GPIO_PORTA_DEN_R |= 0x20;
GPIO_PORTF_DIR_R |= 0x01;
GPIO_PORTF_DEN_R |= 0x01;
    /* initialize ADC0 */
   ADC0_ACTSS_R &= ~1;        /* disable SS0 during configuration */
   ADC0_EMUX_R &= ~0x000F;    /* software trigger conversion */
   ADC0_SSMUX0_R |= 0x05  ;         /* get input from channel 4 */
   ADC0_SSCTL0_R |= 0x06;        /* take one sample at a time, set flag at 1st sample */
   ADC0_ACTSS_R |= 0x01;           /* enable ADC0 sequencer 0 */
   
   
 LCD_init(); //LCD 16x2 initializing
 LCD_row1(); //Cursor position at 1st line
 LCD_puts("Interfacing");
    LCD_row2(); //Cursor position at 2nd line
    LCD_puts("Analog KEYPAD");
    SysCtlDelay(5000000);
    LCD_clear();
while(1)
    {
    ADC0_PSSI_R |= 1;        /* start a conversion sequence 0 */
    while((ADC0_RIS_R & 1) == 0) ;   /* wait for conversion complete */
    ui32ADC0Value = ADC0_SSFIFO0_R; /* read conversion result */
    ADC0_ISC_R = 1;          /* clear completion flag */
    Temp_val = ui32ADC0Value/10;
Dig_val = key_scan(Temp_val);//compare the key pressed
SysCtlDelay(50000);
LCD_row1();
LCD_puts("Press any Key");
LCD_row2();
if(Dig_val <= 'F')//if the ascii is less or equal to F put the value in LCD
LCD_putc(Dig_val);
}
}


unsigned char key_scan(unsigned int volatile rec_val)
{

     if(  rec_val==373 || rec_val == 374) return '0';    // 0 key pressed
else if( rec_val == 376 || rec_val == 377 )  return '1';  // 1st key pressed
else if( rec_val == 380 || rec_val == 379 || rec_val == 380)  return '2';    // 2nd key pressed
else if( rec_val == 381 || rec_val == 382)  return '3';  // 3rd key pressed
else if( rec_val == 357 || rec_val == 358 || rec_val == 359)  return '4';     // 4th key pressed
else if( rec_val == 362 || rec_val == 363 || rec_val == 364)  return '5';     // 5th key pressed
else if( rec_val == 367 || rec_val == 368 || rec_val == 369)  return '6';     // 6th key pressed
else if( rec_val == 371 || rec_val == 372)  return '7';   // 7th key pressed
else if( rec_val == 317 || rec_val == 318 || rec_val == 319)  return '8';     // 8th key pressed
else if( rec_val == 333 || rec_val == 334 || rec_val == 335)  return '9';   // 9th key pressed
else if( rec_val == 345 || rec_val == 346 || rec_val == 347)  return 'A';   // A  key pressed
else if( rec_val == 353 || rec_val == 354 || rec_val == 355)  return 'B';   // B key pressed
else if( rec_val == 0)    return 'C';   // C key pressed
else if( rec_val == 203 || rec_val == 204 || rec_val == 205)  return 'D';     // D key pressed
else if( rec_val == 272 || rec_val == 273 || rec_val == 274)  return 'E'; // E key pressed
else if( rec_val == 306 || rec_val == 307 || rec_val == 308)  return 'F';   // F key pressed
else
return 'G';

}

void LCD_puts(unsigned char *lcd_string)
{
      while (*lcd_string)
      {
              LCD_putc(*lcd_string++);
      }
}

void LCD_init()
{
SysCtlDelay(500000);
    LCD_command(0x30);
SysCtlDelay(500000);
    LCD_command(0x30);
SysCtlDelay(500000);
    LCD_command(0x30);
SysCtlDelay(500000);
    LCD_command(0x20);
SysCtlDelay(500000);
 LCD_command(0x20);
SysCtlDelay(500000);
    LCD_command(0x28); //Selecting 4bit LCD 16x2
SysCtlDelay(500000);
    LCD_command(0x0C); //LCD cursor off
SysCtlDelay(500000);
    LCD_command(0x06); //LCD display on
SysCtlDelay(500000);
    LCD_command(0x01); //LCD clear screen
SysCtlDelay(500000);
}

unsigned char PP1 = 0x00;
void LCD_putc(unsigned char ascii)
{
unsigned char volatile  num;
num = ascii;

// here reversing the bits of lcd_data
//e.g 00110011 will become 110110
num = ((num & 0x11)<<3)| ((num & 0x22)<<1)|((num & 0x44)>>1)|((num & 0x88)>>3);
ascii = num;
//Sending higher nibble of lcd data
    PP1 = (PP1 & 0xF0)|((ascii>>4) & 0x0F);
PP1 = PP1 | 0xA0; // setting 7th pin as high RS = 1, EN = 1;
PP1 = PP1 & ~(0x40); //RW = 0

//shifting data bits to shift register
shift_out1(PP1);
SysCtlDelay(500);
PP1 = PP1 & ~(0x20); // En = 0
shift_out1(PP1);
SysCtlDelay(500);
//Sending lower nibble of lcd data
    PP1 = (PP1 & 0xF0)|(ascii & 0x0F);
PP1 = PP1 | 0xA0; // setting 7th bit as high RS = 1, EN = 1;
PP1 = PP1 & ~(0x40); //RW = 0
shift_out1(PP1);
SysCtlDelay(500);
PP1 = PP1 & ~(0x20); // EN = 0
shift_out1(PP1);
SysCtlDelay(500);
}

void shift_out1(unsigned char str)
{
   unsigned char j=0,check;

GPIO_PORTA_DATA_R = 0x00;   //PA5 pin(stk) is low (0000 0000)
for(j=0;j<=7;j++)
{
     
GPIO_PORTE_DATA_R = 0x00;   //PE3 pin(sclk) is low (0000 0000)
check = (str &(1<<j));
if(check)

GPIO_PORTE_DATA_R |= 0x04;   //PE2 pin(sdat) is high (0000 0100)
else

GPIO_PORTE_DATA_R = 0x00;   //PE2 pin(sdat) is low (0000 0000)

GPIO_PORTE_DATA_R |= 0x08;   //PE3 pin(sclk) is high (0000 1000), sclk=1;
}

GPIO_PORTA_DATA_R |= 0x20;   //PA5 pin(stk) is high (0010 0000) , stk=1,storing completed;
}

unsigned char PP0 = 0x00;
void LCD_command(unsigned char command)
{
unsigned char volatile num;
num = command;
// here reversing the bits of lcd_command
//e.g 00110011 will become 11001100
num = ((num & 0x11)<<3)| ((num & 0x22)<<1)|((num & 0x44)>>1)|((num & 0x88)>>3);
command = num;
//Sending higher nibble of lcd data
    PP0 = (PP0 & 0xF0)|((command>>4) & 0x0F);//ok
PP0 = PP0 & (~(3 << 7)); //  setting 7th pin as low RS = 0 , RW = 0
PP0 = PP0 | 0x20; // EN = 1
//shifting bits to shift register
shift_out1(PP0);
SysCtlDelay(500);
PP0 = PP0 & ~(0x20); //EN = 0
shift_out1(PP0);
SysCtlDelay(500);
//Sending lower nibble of lcd command
    PP0 = (PP0 & 0xF0)|(command & 0x0F);
PP0 = PP0 & (~(3 << 7));   // RS = 0,RW = 0
PP0 = PP0 | 0x20; // EN = 1
//Sending lower nibble of lcd command
shift_out1(PP0);
SysCtlDelay(500);
PP0 = PP0 & ~(0x20); // EN = 0
shift_out1(PP0);
SysCtlDelay(500);
}
