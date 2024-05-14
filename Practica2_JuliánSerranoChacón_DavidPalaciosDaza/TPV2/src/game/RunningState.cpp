// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/Puntuation.h"
#include <math.h>

#include "Game.h"

RunningState::RunningState():
		ihdlr(ih()) //
		{
	auto mngr = Game::instance()->getMngr();
	pacmanSys_ = mngr->addSystem<PacManSystem>();
	renderSys_ = mngr->addSystem<RenderSystem>();
	collisionSys_ = mngr->addSystem<CollisionsSystem>();
	ghostSystem_ = mngr->addSystem<GhostSystem>();
	foodSys_ = mngr->addSystem<FoodSystem>();
	immunitySys_ = mngr->addSystem<ImmunitySystem>();
	puntuationSys_ = mngr->addSystem<PuntuatuionSystem>();
} 

RunningState::~RunningState() {
}

void RunningState::leave() {
	auto mngr = Game::instance()->getMngr();

	mngr->refresh();
}

void RunningState::update() {
	Uint32 startTime = sdlutils().currRealTime();
	auto mngr = Game::instance()->getMngr();
	pacmanSys_->update();
	ghostSystem_->update();
	immunitySys_->update();
	collisionSys_->update();
	renderSys_->update();
	foodSys_->update();
	mngr->refresh();

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	Uint32 frameTime = sdlutils().currRealTime() - startTime;

	if (frameTime < 50){
		SDL_Delay(50 - frameTime);
	}
}

void RunningState::enter() {
	Game::instance()->getMngr()->flushMessages();
	sdlutils().soundEffects().at("intro");
}

void RunningState::onPacManDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (pacmanSys_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
