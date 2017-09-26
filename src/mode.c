#include <msp430g2553.h>
#include "mode.h"
#include "storage.h"

void mode_init() {
	P2DIR &= ~(PROGRAMMING + LEGACY); // Register the mode select ports as inputs.
	P2REN |=  (PROGRAMMING + LEGACY); // Enable the pulling resistors of the inputs.
	P2OUT &= ~(PROGRAMMING + LEGACY); // Pull down the inputs as a default.
	P2IES &= ~(PROGRAMMING + LEGACY); // Select lohi edge.

	P2IFG &= ~(PROGRAMMING + LEGACY); // Reset the interrupt flag or initialise it.
	P2IE  |=  (PROGRAMMING + LEGACY); // Enable the interrupts.
}

// This function is called whenever there is a change on Port 2, hence it will
// always change the mode according to the current state of the port.
// XXX: Currently this simply adjusts the state, but there might be some cleanup
// to do in case the user changes the state when a save operation to the EEPROM
// for instance is in progress.
void __attribute((interrrupt(PORT2_VECTOR))) mode_change_interrupt(void) {
	// Flip the mode bits for the interrupt that was caught.
	MODE ^= P2IFG & (PROGRAMMING + LEGACY);

	// TODO: Due to lack of specs I gathered, the Legacy-Mode is currently not enabled.
	if (MODE & PROGRAMMING) {
		start_recording();
	}
	else if (!(MODE & PROGRAMMING)) {
		start_playing_memory();
	}

	P2IFG &= ~(PROGRAMMING + LEGACY);     // Wait for the next interrupt.
}
