// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawPacMan();
}

void RenderSystem::drawPacMan() {/*
	auto e = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto tr = mngr_->getComponent<Transform>(e);
	auto tex = mngr_->getComponent<Image>(e)->tex_;
	draw(tr, tex);*/

}

void RenderSystem::draw(Transform *tr, Texture *tex) {
}
