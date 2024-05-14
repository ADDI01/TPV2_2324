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
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);

	if (pacman != nullptr)
		if (mngr_->getComponent<Inmunity>(pacman)->getInmunnity()) {
			Uint32 currInmunityTime = sdlutils().currRealTime() - startInmunityTime;

			if (currInmunityTime >= 5000) {
				Message m;
				m.id = _m_IMMUNITY_END;
				mngr_->send(m);
			}
		}
}

void ImmunitySystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_START:
		startInmunityTime = sdlutils().currRealTime();
		break;
	default:
		break;
	}
}
