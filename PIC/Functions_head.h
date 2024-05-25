
#include <xc.h> 
#include <stdint.h>
#include <stdbool.h>
#include <pic18f4580.h>

void uart_init(uint8_t gen_reg, unsigned sync,unsigned brgh, unsigned brg16);
void uart_send(uint8_t *c);
void uart_send_string(uint8_t *c);
void set_portd_based_on_percentage(float percentage);
void Turn_on_pump(float percentage);


