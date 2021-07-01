#include "StatusLED.h"
#include <Arduino.h>

StatusLED::StatusLED(int pin, unsigned long shortBlinkTime,
			unsigned long longBlinkTime, unsigned long blinkPause,
			unsigned long pause, bool inverted):
	pin(pin), inverted(inverted), shortBlinkTime(shortBlinkTime), longBlinkTime(longBlinkTime),
	blinkPause(blinkPause), pause(pause), bitfield(0), indexMod(1), currentIndex(0)
{}

StatusLED::StatusLED(int pin, bool inverted):
	StatusLED(pin, 200, 400, 400, 1000, inverted)
{}

void StatusLED::setOutput(bool state)
{
	digitalWrite(pin, state ^ inverted);
}

void StatusLED::reset()
{
	currentIndex = 0;
	setOutput(false);
	time = millis() + pause;
}

void StatusLED::setStatus(uint8_t status, uint8_t bitCount)
{
	indexMod = 1 + 2 * bitCount;
	bitfield = status;
	reset();
}

/* Index:
 * index == 0 -- pause between status byte blinks, skipped if bit number is not 0
 * (index - 1) / 2 is current bit number
 * (index - 1) % 2: pause between bits
 * 0 -- on time
 * 1 -- off time
 */

void StatusLED::update()
{
	if (time > millis()) {
		return;
	}

	currentIndex = (currentIndex + 1) % indexMod;

	if (currentIndex == 0) { // pause
		reset();
		return;
	}

	uint8_t bitnum = (currentIndex - 1) / 2;
	uint8_t state = (currentIndex - 1) % 2;
	bool isLongBit = bitfield & (1 << bitnum);
	unsigned long onTime = (isLongBit ? longBlinkTime : shortBlinkTime);
	if (state == 0) { // on time
		setOutput(true);
		time = millis() + onTime;
		return;
	}
	// off time
	setOutput(false);
	time = millis() + blinkPause;
}

