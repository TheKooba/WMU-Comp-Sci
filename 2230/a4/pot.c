/* 
 * Author: Richard Schaefer
 * Date  : 15 November 2017
 * Desc. : Program that uses the 
 *         MSP430's Potentiometer
 *	   and Speaker for sound.
 */

#include <msp430.h>
#include <stdlib.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>
#include "dtc.h"

// Global Variables
unsigned int result = 0;

int press = 0;

// Create struct for Notes
typedef struct _note_t {
	int pitch;
	struct _note_t *next;
} note_t;

// Linked List initialization
note_t *HEAD = NULL;
note_t *cur  = NULL;

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
	
	// Setting up Linked List
	HEAD = malloc(sizeof(note_t));
	
	HEAD->pitch = 0;
	HEAD->next  = NULL;
	cur = HEAD;
	
	// More initialization
	initialize_dtc(INCH_4, &result);
	serial_init(9600);
	
	// P1 Pins
	P1SEL  &= ~BIT1;
	P1SEL2 &= ~BIT1;
	
	// P1 Pins
	P1DIR |= BIT6;
	P1SEL |= BIT6;
	
	// Clock Initialization
	//TA0CCR0 = 7000-1;
	TA0CCTL1 = OUTMOD_4;
	TA0CTL = TASSEL_2 + MC_1 + ID_3;
	
	// Initializing TA1
	TA1CTL   = TASSEL_2 | MC_1 | ID_3;
	TA1CCTL0 = CCIE;
	
	
	// Enable global interrupts
	__eint();
	
	// Infinite For-Loop
	for (;;) {
		
		TA0CCR0 = result;
		
	}
	
	// Program will never reach this
	return 0;
	
}

// METHOD: Double Press
#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer(void) {
	
	// Reset the timer
	TA1CCR0 = 0;
	
	// Single Press
	if (press == 1) {
		
		// Set Linked List for notes
		cur->next  = malloc(sizeof(note_t));
		cur->pitch = result;
		cur        = cur->next;
		cur->pitch = 0;
		cur->next  = NULL;
	}
	
	// Double Press
	if (press == 2) {
		
		// Replay the notes
		note_t *temp = HEAD;
		while (temp != NULL) {
			
			TA0CCR0 = temp->pitch;
			__delay_cycles(500000);
			//cio_printf("%i\n\r", temp->pitch);
			temp = temp->next;
		}
		
	}
	
	// Reset the press variable
	press = 0;
	
}

// METHOD: Single Press
#pragma vector=PORT1_VECTOR
__interrupt void button(void) {
	
	// Increment the press var
	press++;
	
	// Set TA1 to 1/4 second
	TA1CCR0 = 31250;
	
	// De-bouncing
	while (!(BIT3 & P1IN));
	__delay_cycles(32000);
	P1IFG &= ~BIT3;
	
}
