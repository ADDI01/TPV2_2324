#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Inmunity.h"
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
}

void GhostSystem::update()
{
	timeGhostGenerator();
	moveGhosts();
}

int GhostSystem::update_lives(int l)
{
	return 0;
}

void GhostSystem::createGhost()
{
	ecs::Entity* ghost = mngr_->addEntity(ecs::grp::GHOSTS);

	int s = 50.0f;
	int x;
	int y;
	chooseCornerToSpawn(x, y,s);

	mngr_->addComponent<Transform>(ghost, Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman_sprites"), 8, 8, 4, 0, 128, 128, 4, 0, 1, 8);

	nGhosts++;
}

void GhostSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_START:
		lastTimeGeneratedGhost_ = sdlutils().virtualTimer().currTime();
		break;
	case _m_PACMAN_GHOST_COLLISION:
		onGhostDie(m.pacman_ghost_collision_data.ghost);
		break;

	case   _m_ROUND_OVER:
		killAllGhosts();
		break;
	case  _m_GAME_OVER:
		killAllGhosts();
		break;
	case  _m_IMMUNITY_START:
		changeGhostsLook(0,6,8,1);
		break;
	case _m_IMMUNITY_END:
		changeGhostsLook(0, 4, 8, 1);
		break;
	default:
		break;
	}
}



void GhostSystem::onGhostDie(ecs::Entity* ghostDead)
{
	sdlutils().soundEffects().at("chomp").play();
	mngr_->setAlive(ghostDead, false);
	nGhosts--;
}

void GhostSystem::killAllGhosts()
{
	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	nGhosts = 0;
	for (ecs::Entity* ghost : ghosts)
		mngr_->setAlive(ghost, false);
}

void GhostSystem::chooseCornerToSpawn(int& x, int& y, int s)
{
	int chooseP = sdlutils().rand().nextInt(0, 4);
	switch (chooseP)
	{
	case 0:
		x = 0;
		y = 0;
		break;
	case 1:
		x = sdlutils().width() - s;
		y = 0;
		break;
	case 2:
		x = 0;
		y= sdlutils().height() - s;
		break;
	case 3:
		x = sdlutils().width() - s;
		y = sdlutils().height() - s;
		break;
	default:
		break;
	}
}

void GhostSystem::moveGhosts()
{
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);

	for (ecs::Entity* ghost : ghosts) {

		Transform* ghostTR = mngr_->getComponent<Transform>(ghost);
		if (sdlutils().rand().nextInt(0, 1001) < 5) {

			Transform* pacmanTR = mngr_->getComponent<Transform>(pacman);
			ghostTR->getVel().set((pacmanTR->getPos() - ghostTR->getPos()).normalize() * 1.1f);
		}

		ghostTR->setPos(ghostTR->getPos() + ghostTR->getVel());
	}
}

void GhostSystem::timeGhostGenerator()
{
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedGhost_ + 5000) {
		if (!mngr_->getComponent<Inmunity>(mngr_->getHandler(ecs::hdlr::PACMAN))->getInmunnity() && nGhosts < 10)
			createGhost();
		lastTimeGeneratedGhost_ = sdlutils().virtualTimer().currTime();
	}
}

void GhostSystem::changeGhostsLook(int scol, int srow, int ncol,int nrow)
{
	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	for (ecs::Entity* ghost : ghosts) {
		mngr_->getComponent<ImageWithFrames>(ghost)->setNewFrame(scol,srow,ncol,nrow);
	}
}
