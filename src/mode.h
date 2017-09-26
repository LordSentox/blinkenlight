// Check the mode that this device is currently in. The mode can only externally
// be changed and a mode change is triggered by an interrupt on one of the ports
// that is used to set it.
// Currently those are three ports.
// Pin 11 can switch sound mode on (active high) in which the programming is done
// by sound-waves instead of an electronic signal. If the device is not in
// programming mode, the current sound-level is being output to the led-driver.
// Pin 12 enables legacy-mode (active high). The programming swith is then instead
// used to switch between constant on of the LED (active high) or pulse (low).
// Pin 13 is used to switch on programming mode (active high), where signal is
// captured and saved into the buffer array. When first switching off programming
// mode, the sequnce is saved into the EEPROM and then it starts running. (TODO)
#ifndef MODE_H
#define MODE_H

unsigned char MODE;
#define PROGRAMMING 0x0020 // Programming is BIT5
#define LEGACY      0x0010 // Legacy is BIT4

void mode_init();

#endif
