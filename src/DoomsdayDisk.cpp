#include "DoomsdayDisk.h"
#include <Arduino.h>

void Bas::Elerion::DoomsdayDisk::startSpinning()
{
	int constrainedMaxSpeed = constrain(maxRelativeSpeed, 0, 255);
	int constrainedMinSpeed = constrain(minRelativeSpeed, 0, maxRelativeSpeed);
	currentRelativeSpeed = random(constrainedMinSpeed, constrainedMaxSpeed + 1);

	const unsigned long maxMilliseconds = 3600000;
	unsigned long constrainedMaxDuration = constrain(maxDuration, 0, maxMilliseconds);
	unsigned long constrainedMinDuration = constrain(minDuration, 0, maxDuration);
	currentDuration = random(constrainedMinDuration, constrainedMaxDuration + 1);

	isRotatingClockwise = random(0, 2);

	delayedFunction.begin(currentDuration, [this]{ startSpinning(); });

	Serial.print("Disk ");
	Serial.print(diskIndex);
	Serial.print(" started spinning at relative speed ");
	Serial.print(currentRelativeSpeed);
	Serial.print(" for ");
	Serial.print(currentDuration);
	Serial.print(" milliseconds in ");
	if (isRotatingClockwise)
	{
		Serial.print("clockwise");
	}
	else
	{
		Serial.print("counter-clockwise");
	}
	Serial.println(" direction.");
}

void Bas::Elerion::DoomsdayDisk::startTestMode()
{
	int constrainedMaxSpeed = constrain(maxRelativeSpeed, 0, 255);
	currentRelativeSpeed = constrainedMaxSpeed;

	isRotatingClockwise = willRunClockwiseInTestMode;

	Serial.print("Disk ");
	Serial.print(diskIndex);
	Serial.print(" started test mode at relative speed ");
	Serial.print(currentRelativeSpeed);
	Serial.print(" in ");
	if (isRotatingClockwise)
	{
		Serial.print("clockwise");
	}
	else
	{
		Serial.print("counter-clockwise");
	}
	Serial.println(" direction.");
}

Bas::Elerion::DoomsdayDisk::DoomsdayDisk(unsigned long minDuration, unsigned long maxDuration, int minRelativeSpeed, int maxRelativeSpeed, int motorPin1, int motorPin2, int maxSpeedOverridePin, bool willRunClockwiseInTestMode)
	: minDuration{minDuration}, maxDuration{maxDuration}, minRelativeSpeed{minRelativeSpeed}, maxRelativeSpeed{maxRelativeSpeed}, motorPin1{motorPin1}, motorPin2{motorPin2}, maxSpeedOverridePin{maxSpeedOverridePin}, willRunClockwiseInTestMode{willRunClockwiseInTestMode}
{
	static int numDisks{0};
	diskIndex = numDisks;
	numDisks++;
}

void Bas::Elerion::DoomsdayDisk::begin(Mode mode)
{
	Serial.print("Initializing disk ");
	Serial.print(diskIndex);
	Serial.print(" in ");

	if (mode == Mode::normal)
	{
		Serial.println("normal mode.");
		startSpinning();
	}
	else
	{
		Serial.println("test mode.");
		startTestMode();
	}
}

void Bas::Elerion::DoomsdayDisk::update(Mode mode)
{
	if (mode != currentMode)
	{
		Serial.print("Disk ");
		Serial.print(diskIndex);
		Serial.print(" mode changed to ");

		if (mode == Mode::test)
		{
			Serial.println("test mode.");
			delayedFunction.cancel();	// Stop waiting for the next cycle.
			startTestMode();
		}
		else
		{
			Serial.println("normal mode.");
			startSpinning();
		}


		currentMode = mode;
	}

	delayedFunction.update();

	int maxOverrideSpeed = map(analogRead(maxSpeedOverridePin), 0, 1023, 0, 255);
	int absoluteSpeed = map(currentRelativeSpeed, 0, 255, 0, maxOverrideSpeed);

	if (isRotatingClockwise)
	{
		analogWrite(motorPin1, absoluteSpeed);
		analogWrite(motorPin2, LOW);
	}
	else
	{
		analogWrite(motorPin1, LOW);
		analogWrite(motorPin2, absoluteSpeed);
	}
}