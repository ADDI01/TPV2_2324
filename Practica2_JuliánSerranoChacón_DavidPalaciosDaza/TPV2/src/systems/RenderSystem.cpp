// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../systems/Puntuation.h"

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
	drawPuntuation();
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

void RenderSystem::drawPuntuation()
{
	PuntuatuionSystem* punt = mngr_->getSystem<PuntuatuionSystem>();
	if (punt != nullptr) {
		int p = punt->getScore();

		std::string msg = "P: " + std::to_string(p);

		Texture info(sdlutils().renderer(), msg,sdlutils().fonts().at("ARIAL24"), build_sdlcolor(color_rgba(4)));

		SDL_Rect dest = build_sdlrect(sdlutils().width() - info.width(), 0, info.width(), info.height());

		info.render(dest);
	}
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
}

uint32_t RenderSystem::color_rgba(const uint8_t tile)
{
	uint32_t c = color(tile);
	return (c << 8) | (c >> 24 & 0xff);
}

uint32_t RenderSystem::color(const uint8_t tile)
{
	switch (tile) {
	case 1:
		return 0x00AA0000; // Red.
	case 2:
		return 0x0000AA00; // Green.
	case 3:
		return 0x000000AA; // Blue.
	case 4:
		return 0x00FFFF00; // Yellow
	case 5:
		return 0x0000FFFF; //Cyan/Aqua
	case 6:
		return 0x00FF00FF; // Magenta/Fuchsia
	case 7:
		return 0x00C0C0C0; // Silver
	case 8:
		return 0x00808080; // Gray
	case 9:
		return 0x00800000; // Maroon

		// from 10 on are colors of fighters
	case 10:
		return 0x00808000; // Olive
	case 11:
		return 0x00008000; // Green
	case 12:
		return 0x00800080; // Purple
	case 13:
		return 0x00008080; // Teal
	case 14:
		return 0x00000080; // Navy
	default:
		return 0x00f260b0; // Kind of dark green
	}
}
