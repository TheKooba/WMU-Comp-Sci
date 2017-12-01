#include <msp430.h>

int main(void)
{

	WDTCTL  = WDTPW | WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL  = CALDCO_1MHZ;
	
	P1DIR = BIT6;
	P1SEL = BIT6;
	
	TA0CTL   = TASSEL_2 | MC_0 | ID_3;
	TA0CCR0  = 31250 - 1; // 31250 - 1;
	// TA0CCR1  = 100 - 1;
	TA0CCTL1 = OUTMOD_4;
	
	P2DIR = BIT1;
	P2SEL = BIT1;
	
	TA1CTL   = TASSEL_2 | MC_1 | ID_3;
	TA1CCR0  = 62500 - 1;
	// TA1CCR1  = 100 - 1;
	TA1CCTL1 = OUTMOD_4;
	
	__bis_SR_register(LPM0_bits);
	
	return 0;
}

