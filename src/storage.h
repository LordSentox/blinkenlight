// This file is used to save a blinking sequence to EEPROM or read a blinking
// sequence from EEPROM.
// Currently, the EEPROM can only hold one single sequence.
// This sequence is simply saved at the start of memory and it's end is marked
// by null termination. The layout of the cells should be as followed:
// xxxxxxxx.xxyyyyyy.yyyyyyyy.yyyyyyyy
// 10 bits for the adc value followed by 22 bits for a time this value is held in
// milliseconds.
// XXX: Obviously those 22 bits for the time value is a bit overkill. (Pun not intended)
// When we want to save more sequences it might make sense to change this. I have
// only chosen this value based on the 32 bit page size of the EEPROM I used.

// The current into which is either currently being saved (programming) or that
// is currently read and being executed (running).
unsigned int seq_state;
cur_sequence = unsigned char[256];

void start_recording_electric();
void start_recording_acustic();
void start_playing_memory();
