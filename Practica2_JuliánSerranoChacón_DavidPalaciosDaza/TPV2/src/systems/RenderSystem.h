// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Texture;
struct Transform;

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::RENDERSYSTEM)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawPacMan();
	void drawGhosts();
	void drawFoods();
	void drawPuntuation();
	void draw(Transform *tr, Texture *tex);

	//código de la p 3
	// Returns a color value (RGBA) from a decimal tile value.
	// Why we need it? For some reason, the texture used in the original wolf
	// uses ARGB, and for Textures in SDLUtils we use RGBA. I tried to change the
	// one of littlewolf to use RGBA with no success ...
	uint32_t color_rgba(const uint8_t tile);
	//código de la p 3
	// Returns a color value (ARGB) from a decimal tile value.
	// Tile 1-9 represent walls, 10- are for players, 0 is not handled
	// because it is an empty cell
	uint32_t color(const uint8_t tile);
};