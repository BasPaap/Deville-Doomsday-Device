#include <Arduino.h>
#include "DoomsdayDisk.h"
#include <Bas.Button.h>
const int innerDiskPin1 = 3;
const int innerDiskPin2 = 5;
const int middleDiskPin1 = 6;
const int middleDiskPin2 = 9;
const int outerDiskPin1 = 10;
const int outerDiskPin2 = 11;
const int maxSpeedOverridePin = A0;
const int testButtonPin = 2;

Bas::Button testButton{testButtonPin, 500};
Bas::Elerion::DoomsdayDisk innerDisk{10000, 20000, 0, 255, innerDiskPin1, innerDiskPin2, maxSpeedOverridePin, true};
Bas::Elerion::DoomsdayDisk middleDisk{10000, 20000, 0, 255, middleDiskPin1, middleDiskPin2, maxSpeedOverridePin, false};
Bas::Elerion::DoomsdayDisk outerDisk{10000, 20000, 0, 255, outerDiskPin1, outerDiskPin2, maxSpeedOverridePin, true};

void onTestButtonPressed()
{
	Serial.println("Test button pressed.");
}

void onTestButtonReleased()
{
	Serial.println("Test button released.");
}

Bas::Elerion::DoomsdayDisk::Mode getCurrentMode()
{
	return testButton.isPressed() ? Bas::Elerion::DoomsdayDisk::Mode::test : Bas::Elerion::DoomsdayDisk::Mode::normal;
}

void setup()
{
	// Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial)
		; // wait for serial port to connect. Needed for native USB port only

	Serial.println("Starting Deville Doomsday Device.");

	testButton.begin(onTestButtonPressed, onTestButtonReleased);
	testButton.update();

	Bas::Elerion::DoomsdayDisk::Mode mode = getCurrentMode();

	innerDisk.begin(mode);
	middleDisk.begin(mode);
	outerDisk.begin(mode);
}

void loop()
{
	testButton.update();

	Bas::Elerion::DoomsdayDisk::Mode mode = getCurrentMode();

	innerDisk.update(mode);
	middleDisk.update(mode);
	outerDisk.update(mode);
}