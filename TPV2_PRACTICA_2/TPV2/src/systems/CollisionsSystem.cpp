// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../utils/Collisions.h"

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
	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	checkCollisionsPacmanAndWalls(*pmTR);
	checkCollisionsGhostsAndWalls(ghosts);
	checkCollisionsPacmanAndGhosts(*pmTR, ghosts);
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

void CollisionsSystem::checkCollisionsGhostsAndWalls(std::vector<ecs::Entity*> ghosts)
{
	for (ecs::Entity* ghost : ghosts) {
		Transform* ghostTR = mngr_->getComponent<Transform>(ghost);

		if (ghostTR->getPos().getX() < 0) {
			ghostTR->getPos().setX(0.1f);
			ghostTR->getVel().set(0.0f, 0.0f);
		}
		else if (ghostTR->getPos().getX() + ghostTR->getWidth() > sdlutils().width()) {
			ghostTR->getPos().setX(sdlutils().width() - ghostTR->getWidth());
			ghostTR->getVel().set(0.0f, 0.0f);
		}

		if (ghostTR->getPos().getY() < 0) {
			ghostTR->getPos().setY(0.0f);
			ghostTR->getVel().set(0.0f, 0.0f);
		}
		else if (ghostTR->getPos().getY() + ghostTR->getHeight() > sdlutils().height()) {
			ghostTR->getPos().setY(sdlutils().height() - ghostTR->getHeight());
			ghostTR->getVel().set(0.0f, 0.0f);
		}
	}
}

void CollisionsSystem::checkCollisionsPacmanAndGhosts(Transform& pacmanTR, std::vector<ecs::Entity*> ghosts)
{
	for (ecs::Entity* ghost : ghosts) {
		Transform* ghostTR = mngr_->getComponent<Transform>(ghost);
		if (Collisions::collidesWithRotation( //
			pacmanTR.getPos(), //
			pacmanTR.getWidth(), //
			pacmanTR.getHeight(), //
			pacmanTR.getRot(), //
			ghostTR->getPos(), //
			ghostTR->getWidth(), //
			ghostTR->getHeight(), //
			ghostTR->getRot())) {
			Message m;
			m.id = _m_PACMAN_GHOST_COLLISION;
			m.pacman_ghost_collision_data.e = ghost;
			mngr_->send(m);
		}
	}
}
