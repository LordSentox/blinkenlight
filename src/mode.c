#include <msp430g2553.h>
#include "mode.h"
#include "storage.h"

// Selects the next interrupt edge of the mode pins to be falling if the pin is
// currently high or rising if the pin currently is low, so the updates will work
// on the next time anything changes on the pin.
void update_interrupt_edges() {
	// TODO: I am not sure these work and at the moment I am too lazy to figure out if this
	// is too confusing or not.. Spoiler: It probably is.
	// P2IES |= ( P2IN &  (PROGRAMMING + LEGACY + SOUND)); // Change from lohi to hilo if necessary
	// P2IES &= (~P2IN & ~(PROGRAMMING + LEGACY + SOUND)); // Change from hilo to lohi if necessary

	if (P2IN & PROGRAMMING) P2IES |= PROGRAMMING else P2IES &= ~PROGRAMMING;
	if (P2IN & LEGACY)      P2IES |= LEGACY      else P2IES &= ~LEGACY;
	if (P2IN & SOUND)       P2IES |= SOUND       else P2IES &= ~SOUND;
}

void mode_init() {
	P2DIR &= ~(PROGRAMMING + LEGACY + SOUND); // Register the mode select ports as inputs.
	P2REN |=  (PROGRAMMING + LEGACY + SOUND); // Enable the pulling resistors of the inputs.
	P2OUT &= ~(PROGRAMMING + LEGACY + SOUND); // Pull down the inputs as a default.

	update_interrupt_edges();
	P2IFG &= ~(PROGRAMMING + LEGACY + SOUND); // Reset the interrupt flag or initialise it.
	P2IE |= (PROGRAMMING + LEGACY + SOUND);  // Enable the interrupts.
}

// This function is called whenever there is a change on Port 2, hence it will
// always change the mode according to the current state of the port.
// XXX: Currently this simply adjusts the state, but there might be some cleanup
// to do in case the user changes the state when a save operation to the EEPROM
// for instance is in progress.
void __attribute((interrrupt(PORT2_VECTOR))) mode_change_interrupt(void) {
	// Port 2.5 is pin 13 and therefore programming.
	// Port 2.4 is pin 12 and therefore legacy.
	// Port 2.3 is pin 11 and therefore sound.
	MODE = P2IN & (PROGRAMMING + LEGACY + SOUND); // Update current mode.
	update_interrupt_edges();                     // Switch the necessary edge(s)

	// TODO: Due to lack of specs I gathered, the Legacy-Mode is currently not enabled.
	if (MODE & PROGRAMMING) {
		if (!(MODE & SOUND)) {
			start_recording_electric();
		}
		else {
			start_recording_acustic();
		}
	}
	else if (!(MODE & PROGRAMMING)) {
		if (!(MODE & SOUND)) {
			start_playing_memory();
		}
		else {
			// TODO: This behaviour may be confusing
			start_playing_immediate_sound();
		}
	}

	P2IFG &= ~(PROGRAMMING + LEGACY + SOUND);     // Wait for the next interrupt.
}
