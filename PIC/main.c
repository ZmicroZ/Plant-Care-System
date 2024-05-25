#include <xc.h>
#include <pic18f4580.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "config.h"
#include "Functions_head.h"

#define ADC_RES (5.0/1023.0)
uint8_t data = 0;
bool got_data_bool = false;
uint8_t print_buffer[256] = {0};
float percentage = 0.0;
float adc_volt = 0.0;
uint16_t adc_value =0;




void main(void) {

    OSCCONbits.IRCF = 0x07;
    OSCCONbits.SCS = 0x02;
    while(OSCCONbits.IOFS!=1);
    
    TRISD=0;
    LATD=0;
    uart_init(0x34,0,1,0);//baud 9600
    
    TRISAbits.RA0 = 1;
    TRISBbits.RB0 = 1; // Set RB0 as input

    ADCON1bits.PCFG = 0xE;
    
    ADCON2bits.ADFM = 1;
    ADCON2bits.ACQT = 0x2;//4TAD 
    ADCON2bits.ADCS = 0x4;
    
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
    
    
    


    while (1) {
        ADCON0bits.GODONE = 1;
        while (ADCON0bits.GODONE);

        uint16_t adc_value = (ADRESH << 8) | ADRESL;
        adc_volt = adc_value * ADC_RES;
        percentage = (adc_volt / 5.0) * 100.0;


        sprintf(print_buffer, "Moisture Sensor Levels: %.2f%%\r\n", percentage, INT0IF);
        uart_send_string(print_buffer);
        set_portd_based_on_percentage(percentage);
        Turn_on_pump(percentage);
        
    }
  
}

