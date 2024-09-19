#include <Arduino.h>
#include "TeslaCoil.h"

Bas::Elerion::TeslaCoil::TeslaCoil(int relayPin) : relayPin{relayPin}
{
}

void Bas::Elerion::TeslaCoil::begin()
{
	Serial.println("Starting Tesla Coil");
	pinMode(this->relayPin, OUTPUT);
}

void Bas::Elerion::TeslaCoil::update()
{
	delayedFunction.update();
}

void Bas::Elerion::TeslaCoil::turnOn()
{
	Serial.print("Turning tesla coil ON on pin ");
	Serial.println(this->relayPin);
	digitalWrite(this->relayPin, HIGH);
	delayedFunction.begin(onDurationInMilliseconds, [this]{ turnOff(); });
}

void Bas::Elerion::TeslaCoil::turnOff()
{
	Serial.print("Turning tesla coil OFF on pin");
	Serial.println(this->relayPin);
	digitalWrite(this->relayPin, LOW);
	delayedFunction.begin(offDurationInMilliseconds, [this]{ turnOn(); });
}
