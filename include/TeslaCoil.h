#if !defined(TESLACOIL_H)
#define TESLACOIL_H

#include "DelayedFunction.h"

namespace Bas::Elerion
{
	class TeslaCoil
	{
	private:
		int relayPin;
		Bas::DelayedFunction delayedFunction;
		const int onDurationInMilliseconds = 60000;
		const int offDurationInMilliseconds = 120000;

	public:
		TeslaCoil(int relayPin);
		void begin();
		void update();
		void turnOn();
		void turnOff();
	};
}

#endif // TESLACOIL_H
