// This file is used to save a blinking sequence to EEPROM or read a blinking
// sequence from EEPROM.
// Currently, the EEPROM can only hold one single sequence.
// This sequence is simply saved at the start of memory and it's end is marked
// by null termination. The layout of the cells should be as followed:
// xxxxxxxx.xxyyyyyy.yyyyyyyy.yyyyyyyy
// 14 bits for the adc value followed by 18 bits for a time this value is held in
// milliseconds.

// The current into which is either currently being saved (programming) or that
// is currently read and being executed (running).
unsigned int seq_state;
unsigned char cur_sequence[256];

void start_recording();
void start_playing_memory();
