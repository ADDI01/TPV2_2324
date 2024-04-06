// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/messages.h"
#include"../ecs/Manager.h"
#include "Game.h"

NewGameState::NewGameState():
msg_(sdlutils().msgs().at("newgame")), //
ihdlr(ih()) {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewGameState::~NewGameState() {
}

void NewGameState::leave() {
	Message m;
	m.id = _m_NEW_GAME;
	Game::instance()->getMngr()->send(m,true);
}

void NewGameState::update() {
	if (ihdlr.keyDownEvent()) {

		Game::instance()->setState(Game::NEWROUND);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewGameState::enter() {
}
