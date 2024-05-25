#include <xc.h>
#include "Functions_head.h"

void uart_init(uint8_t gen_reg, unsigned sync,unsigned brgh, unsigned brg16){
    
    TRISCbits.RC6=0;
    
    SPBRG = gen_reg;
    
    RCSTAbits.SPEN = 1;
    BAUDCONbits.BRG16 = brg16;
    
    TXSTAbits.SYNC = sync;
    TXSTAbits.BRGH = brgh;
    TXSTAbits.TXEN = 1;
    
    
}


void uart_send(uint8_t *c){
    TXREG=*c;
    while(TXSTAbits.TRMT==0){
        Nop();
    }
}

void uart_send_string(uint8_t *c){
    uint8_t i=0;
    while(c[i] != '\0'){
        uart_send(&c[i]);
        i++;
    }
}
void set_portd_based_on_percentage(float percentage) {
    LATD &= 0x00; // Clear PORTD0 to PORTD2 by masking with 11111000

    if (percentage >= 0 && percentage < 20) {
        LATD |= 0x01;; // Turn on only PORTD0 for 0-19%
    } else if (percentage >= 20 && percentage < 40) {
        LATD |= 0x02; // Turn on only PORTD1 for 20-39%
    } else if (percentage >= 40 && percentage < 60) {
        LATD |= 0x03; // Turn on PORTD0 and PORTD1 for 40-59%
    } else if (percentage >= 60 && percentage < 80) {
        LATD |= 0x04; // Turn on only PORTD2 for 60-79%
    } else if (percentage >= 80) {
        LATD |= 0x07; // Turn on PORTD0, PORTD1, and PORTD2 for 80-100%
    }
}
void Turn_on_pump(float percentage) {
    LATD &= 0xBF; // Clear bit 6
    if (percentage < 20) {
        LATD |= 0x40; // Set bit 6
    }
}
