// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr) {
}

PacManSystem::~PacManSystem() {
	
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	ecs::Entity* pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman_sprites"),8,8,0,0, 128,128, 0, 0, 1, 4);
	mngr_->addComponent<Health>(pacman,3);
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

