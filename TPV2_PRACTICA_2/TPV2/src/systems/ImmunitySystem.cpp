#include "ImmunitySystem.h"
#include "../sdlutils/SDLUtils.h"

ImmunitySystem::ImmunitySystem()
{
}

ImmunitySystem::~ImmunitySystem()
{
}

void ImmunitySystem::initSystem()
{

}

void ImmunitySystem::update()
{
	Uint32 currInmunityTime = sdlutils().currRealTime() - startInmunityTime;

	if (currInmunityTime >= 10000) {
		Message m;
		m.id = _m_IMMUNITY_END;
	}
}

void ImmunitySystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_START:
		Uint32 startTime = sdlutils().currRealTime();
		setInmunity(true);
		break;
	case _m_IMMUNITY_END:
		setInmunity(false);
		break;
	default:
		break;
	}
}
