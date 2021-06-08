#include <Arduino.h>
#include <StatusLED.h>

StatusLED led(LED_BUILTIN);

void setup()
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	led.update();
	if (Serial.available()) {
		led.setStatus(Serial.read(), 4);
	}
}

