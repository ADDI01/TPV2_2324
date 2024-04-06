#include "Miraculous.h"
#include "../sdlutils/SDLUtils.h"


Miraculous::Miraculous(Uint32 time) : timeOfCreation(time), isMiraculous(false),
	miraculousCD(sdlutils().rand().nextInt(10, 21)), miraculousRemaining(0), startOfMiraculousTime(0)
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

void Miraculous::setStartOfMiraculousTime(float startMrTm)
{
	startOfMiraculousTime = startMrTm;
}
