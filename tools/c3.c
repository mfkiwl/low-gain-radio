/*
	Example code of lighting LEDs on c3 board

	Programmed by William Harrington, Michael Mathis, and Theo Hill
 */
#include "kw0x.h"

int main(void) {

	/* variable for delay loop */
	int i;

	/* set PLL external reference divider (PRDIV0) to 16 */
	MCG.C5 = 0xF;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 = 0x40;

	/* select PLL instead of FLL */
	MCG.C6 = 0x40;

	/* set frequency range select to high frequency range for oscillator
	   and select external reference clock
	 */
	MCG.C2 |= 0x14;

	/* enable external oscillator */
	OSC0.CR = 0x80;

	/* enable clock for all ports */
	SIM.SCGC5 |= 0x3E00;

	/* modify mux to select alt 1 functionality
	   for PTB1, PTB2, PTB17.
	   Alt 1 functionality is just GPIO
	*/
	PORTB.PCR[1] |= 0x100;
	PORTB.PCR[2] |= 0x100;
	PORTB.PCR[17] |= 0x100;

	/* set data direction as output */
	GPIOB.PDDR |= 0x20006;
	
	/* turn all LEDs of by pulling pins high */
	GPIOB.PTOR = 0x20006;

	while(1) {
		/* toggle output with toggle output register */
		/* lights all LEDs on MCU */
	  	GPIOB.PTOR = 0x00004;
		for(i = 0; i < 1000000; ++i);
	}
	return 0;
}
