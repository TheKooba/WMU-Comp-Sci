// CS 2230 | A2 | Richard Schaefer
// Date: 20 October 2017
// Description: C program that utilizes
//		the MSP430's RGB light.

#include <msp430.h>
#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

// Initialize Character Array Variable
char*color;

void rgb(char RED, char GREEN, char BLUE) {

	// Shifts the bits to the correct spot
	// then OR's each to turn on each element
	P2OUT = RED << 0 | GREEN << 1 | BLUE << 2;

}

int main(void) {

	// stop watchdog timer
	WDTCTL  = WDTPW | WDTHOLD;
	
	// run at 1Mhz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL  = CALDCO_1MHZ;
	
	// all P2 pins as outputs
	P2DIR = -1;
	// all P2 pins off
	P2OUT = 0;
	
	// Setting P1 Pins
	P1DIR	=  BIT0;
	P1REN	=  BIT3;
	P1OUT  |=  BIT3;
	P1IE   |=  BIT3;
	P1IES  |=  BIT3;
	P1IFG  &= ~BIT3;
	

	// Communicate at 9600 baud
	serial_init(9600);
	
	// General interrupt enable
	__bis_SR_register(GIE);
	
	// Infinite For Loop
	for(;;) {
		
		// Cycling through each Color
		
		// Color = OFF
		color="OFF";
		rgb(0, 0, 0);
		// OR P2OUT = 0; Without RGB func
		// wait 1 million cycles (1 second)
		__delay_cycles(1000000);
		
		// Color = RED
		color="RED";
		rgb(1, 0, 0);
		__delay_cycles(1000000);
		
		// Color = GREEN
		color="GREEN";
		rgb(0, 1, 0);
		__delay_cycles(1000000);

		// Color = BLUE
		color="BLUE";
		rgb(0, 0, 1);
		__delay_cycles(1000000);

		// Color = PURPLE
		color="PURPLE";
		rgb(1, 0, 1);
		__delay_cycles(1000000);

		// Color = YELLOW
		color="YELLOW";
		rgb(1, 1, 0);
		__delay_cycles(1000000);

		// Color = CYAN
		color="CYAN";
		rgb(0, 1, 1);
		__delay_cycles(1000000);

		// Color = WHITE
		color="WHITE";
		rgb(1, 1, 1);
		__delay_cycles(1000000);

		// toggle red LED
		//P2OUT ^= 1;
		

	} // end of for-loop

	// Program will never reach this
	return 0;

} // end of Main method



#pragma vector=PORT1_VECTOR
__interrupt void print_color(void) {

	// print out the color in here
	cio_printf("%s\r\n", color);
	
	// button debounce
	while (!(BIT3 & P1IN));
	__delay_cycles(32000);
	// clear interrupt flag for P1.3
	P1IFG &= ~BIT3;
	
} // end of print_color method

