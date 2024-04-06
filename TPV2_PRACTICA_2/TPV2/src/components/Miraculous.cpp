#include "Miraculous.h"
#include "../sdlutils/SDLUtils.h"

Miraculous::Miraculous(Uint32 time) : timeOfCreation(time), isMiraculous(false),
	miraculousCD(sdlutils().rand().nextInt(10, 21)), miraculousRemaining(0)
{
}

Miraculous::~Miraculous()
{
}

void Miraculous::setMiraculousity(bool mir)
{
	isMiraculous = mir;
}

void Miraculous::setMiraculousTimer(float mirRm)
{
	miraculousRemaining = mirRm;
}

void Miraculous::setStartOfMiraculousTime(float startMrTm)
{
	startOfMiraculousTime = startMrTm;
}
