/* Filename: dcu.c 
 * Authors: Kevin Oei, Koen van Vliet
 * For Pro-Q2
 * Description: Digital control unit firmware for speaker system
 * Status: - 
 * Notes: 	- Check for MSB in parameters. If high: error condition
 * 			- Implement status LEDs
 */
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "midi.h"
#include "uart.c"


char sb[64];				/* The buffer for the USART input. Incoming MIDI messages are stored in here. */
volatile char rxcnt = 0;	/* rxcnt is used when determining the offset, which is used to pick the right index when reading sb */
volatile char rxp = 0;		/* rxp will loop from (decimal) 0 to 63, used in determining the index of sb that needs to be approached */


void uputc(char c);
void uputs(char str[]);
char ugetc();
char spiSend(char val);
void setPot(char pot,char val);

int main(void) {
	int i;
	

	/* Debug LEDs */
	DDRB = 0xFF;
	/* Setup serial comms (9600-8-n-1) */
    UCSRA = 0x00;
    UCSRB = 0x18 | (1<<7);
    UCSRC = 0x86;
    UBRRH = 0;
    UBRRL = 23;
	
	/* Setup SPI bus (f/2, mode0.0) */
	SPSR = (1<<0);
	SPCR = (1<<7) | (1<<6) | (1<<4);

	/* Reset digital potentiometers (127 is the flat position) */
	static char potpos[6] = {127};
	/* Connect terminals */
	for (i = 0; i < sizeof(potpos); i++) {
		setPot(i,potpos[i]);
	}


	sei();

	/* Main program loop */
    while (1) {
		char cmd, cc, vv;
		char s[50];
		while (rxcnt == 0); /* Wait for buffer to be empty */
		cmd = ugetc();
		if (cmd & 0x80) { /* Check if 0b1xxxxxxx (valid MIDI command) */
			cmd = cmd & 0xF0; /* Only the 4 most significant bits are relevant for the switch case */
			while (rxcnt == 0);
			cc = ugetc(); /* Acquire controller number */
			while (rxcnt == 0);
			vv = ugetc(); /* Acquire controller value */
			/* Check command type */
			switch (cmd) {
				/* 0xB0 is control change */
				case 0xB0:	snprintf(s, sizeof(s), "Controller %d = %d", cc, vv);
							uputs(s);
							potpos[(int)cc] = vv;
							setPot(cc,potpos[(int)cc]);
							break;
				/*case 'r':	for (i = 0; i < sizeof(potpos); i++) {
								potpos[i] = 127;
								setPot(i,potpos[i]);
							}
							break; */
				default:	uputs("What?");
			}
		}
	}
    return 0;
}

char spiSend(char val) {
	SPDR = val;						/* Transmit data */
	while ((SPSR & (1<<7)) == 0);	/* Wait for SPI transfer to finish. */
	val = SPDR;						/* Receive data */
	return val;
}

void setPot(char pot,char val) {
	/*spiSend(val);*/
	PORTB = ~(1<<pot);

}

ISR (USART_RXC_vect) {
	char c;
	if (UCSRA & (1<<FE | 1<<DOR | 1<<PE)) {
	    c = UDR;
	    uputc('?');
	}
	else {
	    c = UDR;
	    /*PORTB = ~c;*/
		if (rxcnt < 64) {
			sb[rxp & 63] = c;
			rxp = (rxp + 1) & 63;
			rxcnt++;
		}
		else {
			uputc('!');
		}
	}
}

/* Temporary function for PC debugging */
void uputc(char c) {
	while (~UCSRA & 1<<UDRE);
	UDR = c;
}

/* Temporary function for PC debugging */
void uputs(char str[]) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		uputc(str[i] | 0x80);		/* | 0x80 is debug code*/
	}
}

/* Temporary function for PC debugging */
char ugetc() {
	char c;
	int offset;
	offset = (rxp - rxcnt) & 63;
	c = sb[offset];
	rxcnt--;
	return c;
}


