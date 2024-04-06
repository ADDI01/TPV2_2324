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
	drawGhosts();
	drawFoods();
	sdlutils().presentRenderer();
}

void RenderSystem::drawPacMan() {
	ecs::Entity* pacman = mngr_->getHandler(ecs::hdlr::PACMAN);
	mngr_->render(pacman);
}

void RenderSystem::drawGhosts()
{
	std::vector<ecs::Entity*> ghosts = mngr_->getEntities(ecs::grp::GHOSTS);
	for (ecs::Entity* ghost : ghosts) {
		mngr_->render(ghost);
	}
}

void RenderSystem::drawFoods()
{
	std::vector<ecs::Entity*> foods = mngr_->getEntities(ecs::grp::FOODS);
	for (ecs::Entity* food : foods) {
		mngr_->render(food);
	}
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
}
