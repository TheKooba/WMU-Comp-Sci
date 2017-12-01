/* 
 * Author: Richard Schaefer
 * Date  : 28 October 2017 
 * Desc. : Program that cycles through
 *         4 LED-Modes on the MSP430.
 */

#include <msp430.h>

// Global Variables
int mode = 0;


int main(void) {
	
	// WatchDogTimer & Run @ 1MHZ
	WDTCTL  = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL  = CALDCO_1MHZ;
	
	// Setting P1 Pins
	P1DIR	=  BIT0 | BIT1 | BIT6;
	P1REN	=  BIT3;
	P1OUT  |=  BIT3;
	P1IE   |=  BIT3;
	P1IES  |=  BIT3;
	P1IFG  &= ~BIT3;
	
	// Timer ONE (BLUE)
	TA0CTL   = TASSEL_2 | MC_1 | ID_3;
	TA0CCTL1 = OUTMOD_4;
	//TA0CCTL0 = CCIE;
	TA0CCR1 = 31250-1;
	
	// Timer TWO (GREEN)
	TA1CTL   = TASSEL_2 | MC_1 | ID_3;
	TA1CCTL0 = CCIE;
	TA0CCR0  = 41667-1;
	
	// Enable interrupts
	__eint();
	
	// Infinite For-Loop
	for (;;) {
		
		if (mode < 2) {
			
			P1OUT ^= BIT0;
			__delay_cycles(500000);
		}
		
	} // End of For-Loop
	
	// Program should never reach this
	return 0;
	
} // End of main Method

#pragma vector=TIMER1_A0_VECTOR
__interrupt void blink_green (void) {
	
	P1OUT ^= BIT1;
	
} // End of blink_green Method

#pragma vector=PORT1_VECTOR
__interrupt void button (void) {
	
	mode++;
	mode %= 4;
		
	// MODE1 = Red LED blinks every 1/2 second (using execution loop)
	if (mode == 0) {
		
		//TA0CTL &= ~MC_3;
		//P1SEL  &= ~BIT6;
		
		P1SEL = 0;
		P1OUT = ~BIT6 & ~BIT1;
		TA0CTL = TASSEL_2 | MC_0 | ID_3;
		TA1CTL = TASSEL_2 | MC_0 | ID_3;
			
	}
		
	// MODE2 = Red LED blinks every 1/2 second (using execution loop)
	//	   Green LED blinks every 1/3 second (using timer & interrupt)
	if (mode == 1) {
		
		//TA1CTL |= MC_1;
		
		TA1CTL = TASSEL_2 | MC_1 | ID_3;
		TA1CCR0 = 41667-1;
		
		
	}
		
	// MODE3 = Red LED turns off
	//	   Green LED blinks every 1/3 second (using timer & interrupt)
	//	   Blue LED blinks every 1/4 second (using timer & signal)
	if (mode == 2) {
		
		P1SEL  |= BIT6;
		TA0CTL = TASSEL_2 | MC_1 | ID_3;
		P1OUT  = ~BIT0;
		TA1CCR0 = 41667-1;
			
	}
		
	// MODE4 = Red LED stays off
	//	   Green LED turns off
	//	   Blue LED blinks slower, every 1/2 second (using timer & signal)
	if (mode == 3) {
		
		//TA1CTL &= ~MC_3;
		
		P1OUT  = ~BIT0 & ~BIT1;
		TA0CCR0 = 62500-1;
		TA1CTL = TASSEL_2 | MC_0 | ID_3;
		
	}
	
	// Used for de-bouncing double press
	while (!(BIT3 & P1IN));
	__delay_cycles(32000);
	P1IFG &= ~BIT3;
	
} // End of button Method
