#include <Arduino.h>
#include "DoomsdayDisk.h"

const int innerDiskPin1 = 9;
const int innerDiskPin2 = 10;
const int middleDiskPin1 = 13;
const int middleDiskPin2 = 14;
const int outerDiskPin1 = 1;
const int outerDiskPin2 = 15;
const int maxSpeedOverridePin = A0;

Bas::Elerion::DoomsdayDisk innerDisk {10000, 60000, 0, 255, innerDiskPin1, innerDiskPin2, maxSpeedOverridePin };
Bas::Elerion::DoomsdayDisk middleDisk {10000, 60000, 0, 255, middleDiskPin1, middleDiskPin2, maxSpeedOverridePin };
Bas::Elerion::DoomsdayDisk outerDisk {10000, 60000, 0, 255, outerDiskPin1, outerDiskPin2, maxSpeedOverridePin };

void setup() {
	innerDisk.begin();
	middleDisk.begin();
	outerDisk.begin();
}

void loop() {
	innerDisk.update();
	middleDisk.update();
	outerDisk.update();
}