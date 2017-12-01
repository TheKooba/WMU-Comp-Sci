#include <msp430.h>
#include <stdlib.h>
#include <string.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include "dtc.h"

unsigned int result = 0;

typedef struct _country_t {
	char *name;
	int pop;
	struct _country_t *next;
} country_t;

int main(void) {
    WDTCTL  = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
	
	initialize_dtc(INCH_4, &result);
	serial_init(9600);

	P1SEL  &= ~BIT1;
	P1SEL2 &= ~BIT1;

	P1DIR = BIT1;
	P1OUT = 0;

	country_t  germany = { "Germany", 14 };
	country_t *italy = malloc(sizeof(country_t));
	italy->name = malloc(6);
	strncpy(italy->name, "Italy", 6);

	for(;;) {
		italy->pop = result / 10;
		cio_printf("%i\n\r", italy->pop);
		cio_printf("%s\n\r", germany.name);
		P1OUT ^= BIT1;
		__delay_cycles(1000000);
	}

	return 0;
}

