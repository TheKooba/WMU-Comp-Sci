#include <msp430.h>

int numbers[] = { BIT6, ~(BIT1 | BIT2) };
int digits[] = { BIT3, BIT2, BIT1, BIT0 };
int bin = 0b1010;
int pos = -1;

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL  = CALDCO_1MHZ;
	
	P1DIR = -1;
	P2DIR = -1;
	
	P1OUT = 0;
	P2OUT = 0;
	
	TA0CTL   = TASSEL_2 | MC_1 | ID_0;
	TA0CCTL0 = CCIE;
	TA0CCR0  = 1024;
	
	__bis_SR_register(LPM0_bits | GIE);
	for(;;);

	return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer(void)
{
	P2OUT = 0;

	pos++;
	pos %= 4;

	P1OUT = numbers[(bin >> pos) & 1];

	P2OUT = digits[pos];
}

