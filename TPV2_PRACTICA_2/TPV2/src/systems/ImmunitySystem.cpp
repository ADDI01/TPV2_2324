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
	Uint32 currInmunityTime = sdlutils().currRealTime() - startInmunityTime;

	if (currInmunityTime >= 10000) {
		Message m;
		m.id = _m_IMMUNITY_END;
	}
}

void ImmunitySystem::recieve(const Message& m)
{
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	Inmunity* pmInm = mngr_->getComponent<Inmunity>(pacman);

	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);

	switch (m.id) {
	case _m_IMMUNITY_START:
		startInmunityTime = sdlutils().currRealTime();
		pmInm->setInmunity(true);
		break;
	case _m_IMMUNITY_END:
		pmInm->setInmunity(false);
		break;
	default:
		break;
	}
}
