#if !defined(DOOMSDAYDISK_H)
#define DOOMSDAYDISK_H

namespace Bas::Elerion
{
	class DoomsdayDisk
	{
		unsigned long minDuration;
		unsigned long maxDuration;
		int minRelativeSpeed;
		int maxRelativeSpeed;
		int motorPin1;
		int motorPin2;
		int maxSpeedOverridePin;
		bool isRotatingClockwise;
		int currentRelativeSpeed;
		unsigned long currentDuration;

		void startSpinning();

	public:
		DoomsdayDisk(unsigned long minDuration, unsigned long maxDuration, int minRelativeSpeed, int maxRelativeSpeed, int motorPin1, int motorPin2, int maxSpeedOverridePin);
		void begin();
		void update();
	};
}

#endif // DOOMSDAYDISK_H
