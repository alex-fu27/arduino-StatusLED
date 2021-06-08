#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <stdint.h>

class StatusLED
{
public:
	/*
	 * pin: Pin number of the LED. Must be initialized with pinMode.
	 * shortBlinkTime: (milliseconds) "on" period of bits that are 0.
	 * longBlinkTime: (milliseconds) "on" period of bits that are 1.
	 * blinkPause: (milliseconds) "off" period between bits.
	 * pause: (milliseconds) pause between blink sequences.
	 */
	StatusLED(int pin, unsigned long shortBlinkTime,
			unsigned long longBlinkTime, unsigned long blinkPause,
			unsigned long pause);

	/*
	 * Use default blink periods
	 */
	StatusLED(int pin);

	/*
	 * Set status and number of bits in status.
	 * e.g. status = 0b00001010, bitCount = 5 will set the sequence to be
	 * short long short long short
	 */
	void setStatus(uint8_t status, uint8_t bitCount);

	/*
	 * must be called periodically
	 */
	void update();

private:
	const int pin;
	const unsigned long shortBlinkTime;
	const unsigned long longBlinkTime;
	const unsigned long blinkPause;
	const unsigned long pause;
	uint8_t bitfield;
	uint8_t indexMod;
	uint8_t currentIndex;
	unsigned long time;

	void reset();
};

#endif

