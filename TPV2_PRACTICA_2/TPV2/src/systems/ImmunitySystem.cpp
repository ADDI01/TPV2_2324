#include "ImmunitySystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Inmunity.h"


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
	if (immunity) {
		Uint32 currInmunityTime = sdlutils().currRealTime() - startInmunityTime;

		if (currInmunityTime >= 5000) {
			Message m;
			m.id = _m_IMMUNITY_END;
		}
	}
}

void ImmunitySystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_START:
		startInmunityTime = sdlutils().currRealTime();
		immunity = true;
		break;
	case _m_IMMUNITY_END:
		immunity = false;
		break;
	default:
		break;
	}
}
