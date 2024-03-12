// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

NewGameState::NewGameState():
msg_(sdlutils().msgs().at("newgame")), //
ihdlr(ih()) {

}

NewGameState::~NewGameState() {
}

void NewGameState::leave() {
}

void NewGameState::update() {
}

void NewGameState::enter() {
}
