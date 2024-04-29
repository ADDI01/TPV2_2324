#include "Miraculous.h"
#include "../sdlutils/SDLUtils.h"


Miraculous::Miraculous(Uint32 time, bool startMiraculous) : timeOfCreation(time), isMiraculous_(startMiraculous),
	miraculousCD(sdlutils().rand().nextInt(10000, 21000)), miraculousRemaining(sdlutils().rand().nextInt(1000, 6000)),
	startOfMiraculousTime(sdlutils().currRealTime())
{
}

Miraculous::~Miraculous()
{
}

void Miraculous::setMiraculousity(bool mir)
{
	isMiraculous_ = mir;
}

void Miraculous::setTimeOfCreation(Uint32 time)
{
	timeOfCreation = time;
}

void Miraculous::setMiraculousTimer(float mirRm)
{
	miraculousRemaining = mirRm;
}

void Miraculous::setStartOfMiraculousTime(Uint32  startMrTm)
{
	startOfMiraculousTime = startMrTm;
}
