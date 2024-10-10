#if !defined(DOOMSDAYDISK_H)
#define DOOMSDAYDISK_H

#include "DelayedFunction.h"

namespace Bas::Elerion
{
	class DoomsdayDisk
	{
	public:
		enum class Mode
		{
			normal = 0,
			test
		};

	private:
		int diskIndex;
		unsigned long minDuration;
		unsigned long maxDuration;
		int minRelativeSpeed;
		int maxRelativeSpeed;
		int motorPin1;
		int motorPin2;
		int maxSpeedOverridePin;
		bool isRotatingClockwise;
		bool willRunClockwiseInTestMode;
		int currentRelativeSpeed;
		unsigned long currentDuration;
		Bas::DelayedFunction delayedFunction;
		Mode currentMode;

		void startSpinning();
		void startTestMode();
		void waitForNextSpin();
	public:
		DoomsdayDisk(unsigned long minDuration, unsigned long maxDuration, int minRelativeSpeed, int maxRelativeSpeed, int motorPin1, int motorPin2, int maxSpeedOverridePin, bool willRunClockwiseInTestMode);
		void begin(Mode mode);
		void update(Mode mode);
	};
}

#endif // DOOMSDAYDISK_H
