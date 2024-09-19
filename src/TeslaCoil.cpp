#include <Arduino.h>
#include "TeslaCoil.h"

Bas::Elerion::TeslaCoil::TeslaCoil(int relayPin) : relayPin{relayPin}
{
}

void Bas::Elerion::TeslaCoil::begin()
{
	Serial.println("Starting Tesla Coil");
}

void Bas::Elerion::TeslaCoil::update()
{
	delayedFunction.update();
}

void Bas::Elerion::TeslaCoil::turnOn()
{
	digitalWrite(this->relayPin, HIGH);
	delayedFunction.begin(onDurationInMilliseconds, [this]{ turnOff(); });
}

void Bas::Elerion::TeslaCoil::turnOff()
{
	digitalWrite(this->relayPin, LOW);
	delayedFunction.begin(offDurationInMilliseconds, [this]{ turnOn(); });
}
