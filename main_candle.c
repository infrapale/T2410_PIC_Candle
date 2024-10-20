//#include "16F84A.h"
#include <xc.h>

#define _XTAL_FREQ 4000000

#pragma config FOSC=XT, WDTE=OFF, PWRTE=OFF, CP=OFF,

#define PWM_NBR_BIT   8
#define WAVE_NBR_DATA 8
#define NBR_OF_LED    8
#define WAVE_LEN      16

const uint8_t ratio[WAVE_NBR_DATA] = {
    0b00000000,
    0b00010000,
    0b01000100,
    0b01010101,
    0b01011101,
    0b11101110,
    0b11111110,
    0b11111111
};
const uint8_t bit_mask[PWM_NBR_BIT] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const uint8_t led_iter[NBR_OF_LED] = {100,20,30,40,50,60,70,80};
const uint8_t wave[WAVE_LEN] = {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0};
uint8_t led_pos[NBR_OF_LED] = {0, 4, 2, 6, 8, 10, 12,15};
uint8_t led_iter_cntr[NBR_OF_LED] = {0};
uint8_t led_pattern[NBR_OF_LED];


void delay_ms(uint8_t ms)
{
    for (uint8_t i = 0; i< ms;i++) __delay_ms(10);
}

int main()
{
    TRISA = 0xFF;
    TRISB = 0x00;
    uint8_t lindex;
    uint8_t windex;
    uint8_t p_value;
    
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
          
          led_pattern[lindex] = ratio[wave[led_pos[lindex]]];
      }
      for (uint8_t bindex = 0; bindex < PWM_NBR_BIT; bindex++ )
      {
            p_value = 0x00;  
            for (lindex = 0; lindex <NBR_OF_LED; lindex ++)
            {
                if ((led_pattern[lindex] & bit_mask[bindex]) != 0)
                    p_value = p_value | bit_mask[lindex];
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