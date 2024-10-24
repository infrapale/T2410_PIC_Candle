//#include "16F84A.h"
#include <xc.h>

#define _XTAL_FREQ 4000000

#pragma config FOSC=XT, WDTE=OFF, PWRTE=OFF, CP=OFF,

#define PWM_NBR_BIT   16
#define DUTY_NBR_DATA 32
#define WAVE_NBR_DATA 16
#define NBR_OF_LED    8
#define WAVE_LEN      32

const uint16_t duty_ratio[DUTY_NBR_DATA] = {
    0b0000000000000000,
    0b0000000100000000,
    0b0001000000010000,
    0b0010000100001000,
    0b0100010001000100,
    0b0100100100100100,
    0b0100101001010010,
    0b0101010010101001,
    0b0101010101010101,
    0b0110101011011010,
    0b0110110110110110,
    0b1110110110110110,
    0b1110111011101110,
    0b1111011111011110,
    0b1111111011111110,
    0b1111111011111111,
    0b1111111111111111
};
const uint16_t bit_mask[PWM_NBR_BIT] = 
{
    0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
    0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
};

uint8_t led_iter[NBR_OF_LED] = {10,6,4,20,5,6,3,2};
const uint8_t wave[WAVE_LEN] = 
{
    2,2,3,3,4,5,6,7,8,9,10,11,12,13,14,15,
    15,14,13,12,11,10,9,8,7,6,5,4,3,3,2,2
};
uint8_t     led_pos[NBR_OF_LED] = {0, 8, 10, 12, 14, 16, 20, 30};
uint8_t     led_iter_cntr[NBR_OF_LED] = {0};
uint16_t    led_pattern[NBR_OF_LED];


void delay_ms(uint8_t ms)
{
    for (uint8_t i = 0; i< ms;i++) __delay_ms(10);
}

int main()
{
    TRISA =     0xFF;
    TRISB =     0x00;
    uint8_t     lindex;
    uint8_t     windex;
    uint8_t     p_value;
    
    while(1)
    { 
      p_value = 0x00;  
      for (lindex = 0; lindex < NBR_OF_LED; lindex ++)
      {
          led_iter_cntr[lindex]++;
          if (led_iter_cntr[lindex] >= led_iter[lindex]) 
          {
              led_iter_cntr[lindex] = 0;
              led_pos[lindex]++;
              if (led_pos[lindex] >= WAVE_LEN ) led_pos[lindex] = 0;
          }
           
          led_pattern[lindex] = duty_ratio[wave[led_pos[lindex]]];
      }
      for (uint8_t bindex = 0; bindex < PWM_NBR_BIT; bindex++ )
      {
            p_value = 0x00;  
            for (lindex = 0; lindex <NBR_OF_LED; lindex ++)
            {
                if ((led_pattern[lindex] & bit_mask[bindex]) != 0)
                    p_value = p_value | (uint8_t)bit_mask[lindex];
            }
           PORTB = p_value;
           //delay_ms(1);
      }
    }
    
    //TRISBbits.TRISB7 = 0;
    uint8_t dx = 2;
    while (1)
    {    
        PORTB = 0xFF;
        delay_ms(dx);
        PORTB = 0x00;
        delay_ms(dx);
    }
    while(1)
    {
        PORTBbits.RB7 = 1;
        delay_ms(dx);
        PORTBbits.RB0 = 1;
        delay_ms(dx);
        PORTBbits.RB1 = 1;
        delay_ms(dx);
        PORTBbits.RB1 = 0;
        PORTBbits.RB2 = 1;
        delay_ms(dx);
        PORTBbits.RB2 = 0;
        PORTBbits.RB3 = 1;
        delay_ms(dx);
        PORTBbits.RB3 = 0;
        PORTBbits.RB4 = 1;
        delay_ms(dx);
        PORTBbits.RB4 = 0;
        PORTBbits.RB5 = 1;
        delay_ms(dx);
        PORTBbits.RB5 = 0;
        PORTBbits.RB6 = 1;
        delay_ms(dx);
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
        delay_ms(dx);
        PORTBbits.RB0 = 0;
        
        if (dx > 4 ) dx--;
        else dx = 20;

    }

    return 0;
}