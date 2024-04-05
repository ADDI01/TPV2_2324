// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	Transform* pmTR = mngr_->getComponent<Transform>(pacman);
	checkCollisionsPacmanAndWalls(*pmTR);
}

void CollisionsSystem::checkCollisionsPacmanAndWalls(Transform& pmTR)
{

	if (pmTR.getPos().getX() < 0) {
		pmTR.getPos().setX(0.1f);
		pmTR.getVel().set(0.0f, 0.0f);
	}
	else if (pmTR.getPos().getX() + pmTR.getWidth() > sdlutils().width()) {
		pmTR.getPos().setX(sdlutils().width() - pmTR.getWidth());
		pmTR.getVel().set(0.0f, 0.0f);
	}
	
	if (pmTR.getPos().getY() < 0) {
		pmTR.getPos().setY(0.0f);
		pmTR.getVel().set(0.0f, 0.0f);
	}
	else if (pmTR.getPos().getY() + pmTR.getHeight() > sdlutils().height()) {
		pmTR.getPos().setY(sdlutils().height() - pmTR.getHeight());
		pmTR.getVel().set(0.0f, 0.0f);
	}
}

