#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"

GhostSystem::GhostSystem()
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
	createGhost();
}

void GhostSystem::update()
{
}

int GhostSystem::update_lives(int l)
{
	return 0;
}

void GhostSystem::createGhost()
{
	ecs::Entity* ghost = mngr_->addEntity(ecs::grp::GHOSTS);

	mngr_->addComponent<Transform>(ghost, Vector2D(0, 0), Vector2D(), 50, 50, 0.0f);
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman_sprites"), 8, 8, 4, 0, 128, 128, 4, 0, 1, 8);
}

void GhostSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		onGhostDie(m.pacman_ghost_collision_data.e);

	default:
		break;
	}
}

void GhostSystem::onGhostDie(ecs::Entity* ghostDead)
{
	mngr_->setAlive(ghostDead, false);
	nGhosts--;
}
