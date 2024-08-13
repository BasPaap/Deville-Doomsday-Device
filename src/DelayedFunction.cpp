#include "DelayedFunction.h"

void Bas::DelayedFunction::update()
{
	if (isInitialized &&
		!isCalled &&
		millis() - startTime >= delay)
	{
		isCalled = true;
		callbackCaller.call();
	}
}

void Bas::DelayedFunction::cancel()
{
	isInitialized = false;
}