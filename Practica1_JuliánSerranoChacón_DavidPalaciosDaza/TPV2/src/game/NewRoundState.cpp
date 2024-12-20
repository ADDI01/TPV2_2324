
// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "BlackHolesFacade.h"
#include "MissilesFacade.h"
#include "Game.h"
NewRoundState::NewRoundState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, BlackHolesFacade* blackHoles_mngr, MissilesFacade* missiles_mngr) :
		msg_(sdlutils().msgs().at("newround")), //
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr),
		blackHoles_mngr_(blackHoles_mngr),
		missiles_mngr_(missiles_mngr){
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewRoundState::~NewRoundState() {
}

void NewRoundState::leave() {
}

void NewRoundState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		fighter_mngr_->reset_fighter();
		ast_mngr_->remove_all_asteroids();
		ast_mngr_->create_asteroids(10);
		blackHoles_mngr_->remove_all_blackHoles();
		blackHoles_mngr_->create_blackHoles(6);
		missiles_mngr_->remove_all_missiles();

		Game::instance()->setState(Game::RUNNING);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewRoundState::enter() {
}
