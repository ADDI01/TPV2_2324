// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	sdlutils().clearRenderer();
	drawPacMan();
	sdlutils().presentRenderer();
}

void RenderSystem::drawPacMan() {
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->render(pacman);
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
}
