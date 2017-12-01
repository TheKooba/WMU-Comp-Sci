/*
 * Author : Richard Schaefer
 * Date   : 24 November 2017 
 * Due    : 7 December 2017
 * Project: A5 - Color Display
 */

#include <msp430.h>
#include <stdlib.h>
#include <string.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include "dtc.h"
#include "colors.h"

unsigned int result = 0;

int main(void) {

    // Stop watchdog timer to prevent time out reset
	WDTCTL  = WDTPW | WDTHOLD;
	
	// Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
	
	// Setting all P1 Pins
	P1REN	=  BIT3;
	P1OUT  |=  BIT3;
	P1IE   |=  BIT3;
	P1IES  |=  BIT3;
	P1IFG  &= ~BIT3;
	
	initialize_dtc(INCH_4, &result);
	serial_init(9600);

	P1SEL  &= ~BIT1;
	P1SEL2 &= ~BIT1;

	P1DIR = BIT1;
	P1OUT = 0;	
	
	
	TA1CTL = TASSEL_2 | MC_1 | ID_3;
	TA1CCTL0 = CCIE;
	
	
	// Enable global interrupts
	__eint();
	
	for(;;) {
		
		// __delay_cycles(1000000);
		// TA0CCR0 = result;
		
	}
	
	// Program will never reach this
	return 0;
}
