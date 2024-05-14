// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include "GameState.h"

class InputHandler;
class PacManSystem;
class GhostSystem;
class FoodSystem;
class RenderSystem;
class CollisionsSystem;
class ImmunitySystem;
class PuntuatuionSystem;

class RunningState: public GameState {
public:
	RunningState();
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	void onPacManDeath();
	InputHandler &ihdlr;

	PacManSystem* pacmanSys_;
	FoodSystem* foodSys_;
	GhostSystem* ghostSystem_;
	RenderSystem* renderSys_;
	CollisionsSystem* collisionSys_;
	ImmunitySystem* immunitySys_;
	PuntuatuionSystem* puntuationSys_;
};

