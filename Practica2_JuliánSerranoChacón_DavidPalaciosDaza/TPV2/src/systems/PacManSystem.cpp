// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/Inmunity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
	
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	createPacman();
}

void PacManSystem::update() {
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	InputHandler& ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) {
			pmTR_->setRot(pmTR_->getRot() + 90.0f);
			
			Vector2D* vel = &pmTR_->getVel();
			vel->set(vel->rotate(90.0));
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) {
			pmTR_->setRot(pmTR_->getRot() - 90.0f);
			Vector2D* vel = &pmTR_->getVel();
			vel->set(vel->rotate(-90.0));
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) {
			Vector2D* vel = &pmTR_->getVel();

			vel->set(Vector2D(0.0f, -3.0f).rotate(pmTR_->getRot()));

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) {
			Vector2D* vel = &pmTR_->getVel();
			vel->set(Vector2D(0.0f, 0.0f));

		}
	}

	// move the pacman
	pmTR_->setPos(pmTR_->getPos() + pmTR_->getVel());
}

int PacManSystem::update_lives(int l)
{
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	Health* pacmanH =  mngr_->getComponent<Health>(pacman);
	return pacmanH->update_lives(l);
}

void PacManSystem::recieve(const Message& m)
{

	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	Inmunity* pmInm = mngr_->getComponent<Inmunity>(pacman);

	switch (m.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		onPacmanHitWithGhost();
		break;
	case _m_ROUND_OVER:
		sdlutils().soundEffects().at("death").play();
		Game::instance()->setState(Game::NEWROUND);
		break;
	case _m_GAME_OVER:

		if (m.game_over_data.win) {
			sdlutils().soundEffects().at("won").play();
			Game::instance()->setState(Game::GAMEOVER);
		}
		else {
			sdlutils().soundEffects().at("death").play();
			Game::instance()->setState(Game::GAMEOVER);
		}
		break;
	case _m_ROUND_START:
		pmTR_->setPos(Vector2D((sdlutils().width() - pmTR_->getWidth()) / 2.0f, (sdlutils().height() - pmTR_->getHeight()) / 2.0f));
		pmTR_->getVel().set(0, 0);
		break;
	case _m_NEW_GAME:
		mngr_->getComponent<Health>(mngr_->getHandler(ecs::hdlr::PACMAN))->set_lives(3);
		break;
	case _m_IMMUNITY_START:
		pmInm->setInmunity(true);
		break;
	case _m_IMMUNITY_END:
		pmInm->setInmunity(false);
		break;
	default:
		break;
	}
}

void PacManSystem::killPacman()
{
	mngr_->setAlive(mngr_->getHandler(ecs::hdlr::PACMAN),false);
}

void PacManSystem::onPacmanHitWithGhost()
{
	if (!mngr_->getComponent<Inmunity>(mngr_->getHandler(ecs::hdlr::PACMAN))->getInmunnity()) {
		if (update_lives(-1) > 0) {
			Message m2;
			m2.id = _m_ROUND_OVER;
			mngr_->send(m2);
		}
		else {
			Message m2;
			m2.id = _m_GAME_OVER;
			m2.game_over_data.win = false;
			mngr_->send(m2);
		}
	}
}

void PacManSystem::createPacman()
{
	ecs::Entity* pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman_sprites"), 8, 8, 0, 0, 128, 128, 0, 0, 1, 4);
	mngr_->addComponent<Health>(pacman, 3);
	mngr_->addComponent<Inmunity>(pacman);
}

