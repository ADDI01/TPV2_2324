// This file is part of the course TPV2@UCM - Samir Genaim

#include "Puntuation.h"
#include "../components/Inmunity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
PuntuatuionSystem::PuntuatuionSystem()
{
	score_ = 0;

}

PuntuatuionSystem::~PuntuatuionSystem() {
}

void PuntuatuionSystem::initSystem() {
	score_ = 0;
}

void PuntuatuionSystem::update() {
}

void PuntuatuionSystem::recieve(const Message &m) {
	switch (m.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		if(mngr_->getComponent<Inmunity>(mngr_->getHandler(ecs::hdlr::PACMAN))->getInmunnity())
			score_ += 20;
		break;
	case _m_GAME_OVER:
		score_ = 0;
		break;
	case _m_PACMAN_FOOD_COLLISION:
		score_ += 10;
		break;
	default:
		break;
	}
}
