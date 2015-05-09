#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

ISR(USART_RXC_vect){
	char c;
	if (UCSRA & (1<<FE | 1<<DOR | 1<<PE)) {
	    c = UDR;
	    while (~UCSRA & 1<<UDRE);
	    UDR = '?';
	}
	else {
	    c = UDR;
	    PORTB = ~c;
	}
}

int main(void) {
	float adcval;
    // 9600-7-E-1
    UCSRA = 0x00;
    UCSRB = 0x18 | (1<<7);
    UCSRC = 0xA4;
    UBRRH = 0;
    UBRRL = 23;

	DDRB = 0xFF;
	sei();

    while (1) {
    }
    return 0;
}
