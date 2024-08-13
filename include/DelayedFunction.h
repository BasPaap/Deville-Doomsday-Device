#if !defined(DELAYEDFUNCTION_H)
#define DELAYEDFUNCTION_H

#include <CallbackCaller.h>

namespace Bas
{
	class DelayedFunction
	{
		Bas::CallbackCaller callbackCaller;
		unsigned long startTime;
		unsigned long delay;
		bool isCalled;
		bool isInitialized;

		public:
		template<typename F>
		void begin(unsigned long delayInMilliseconds, F && lambda);
		void update();
		void cancel();
	};

	template <typename F>
	inline void DelayedFunction::begin(unsigned long delayInMilliseconds, F &&lambda)
	{
		callbackCaller.begin(lambda);
		isCalled = false;
		delay = delayInMilliseconds;
		startTime = millis();
		isInitialized = true;
	}
}

#endif // DELAYEDFUNCTION_H
