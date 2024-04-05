// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/System.h"
#include "GameState.h"

class InputHandler;
class PacManSystem;
class GhostSystem;

class RunningState: public GameState {
public:
	RunningState();
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	void checkCollisions();
	void onPacManDeath();
	InputHandler &ihdlr;


	PacManSystem* pacmanSys_;
	//ecs::System* gameCtrlSys_;
	GhostSystem* ghostSystem_;
	ecs::System* renderSys_;
	ecs::System* collisionSys_;
};

