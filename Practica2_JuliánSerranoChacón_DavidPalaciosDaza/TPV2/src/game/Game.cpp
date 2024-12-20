// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "GameOverState.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "WinState.h"

#include "PausedState.h"
#include "RunningState.h"

using ecs::Manager;

Game::Game() :
		mngr_(new Manager()), //
		ihdlr(ih()), //
		current_state_(nullptr), //
		paused_state_(nullptr), //
		runing_state_(nullptr), //
		newgame_state_(nullptr), //
		newround_state_(nullptr), //
		gameover_state_(nullptr) {

}

Game::~Game() {
	delete mngr_;
	mngr_ = nullptr;
	delete paused_state_;
	paused_state_ = nullptr;
	delete runing_state_;
	runing_state_ = nullptr;
	delete newgame_state_;
	newgame_state_ = nullptr;
	delete newround_state_;
	newround_state_ = nullptr;
	delete gameover_state_;
	gameover_state_ = nullptr;
	delete win_state_;
	win_state_ = nullptr;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Pac Man", 800, 600,
			"resources/config/PacMan.resources.json");

	/*AsteroidsFacade* ast_facede = new AsteroidsUtils();
	FighterFacade *fighter_facede = new FighterUtils();
	BlackHolesFacade* blackHoles_facade = new BlackHolesUtils();
	MissilesFacade* missiles_facade = new MissilesUtils();

	fighter_facede->create_fighter();*/

	paused_state_ = new PausedState();
	runing_state_ = new RunningState();
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	gameover_state_ = new GameOverState();
	win_state_ = new WinState();

	current_state_ = newgame_state_;
}

void Game::start() {

// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		current_state_->update();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}