#pragma once
#include <SDL_rect.h>
#include "GameState.h"

class Texture;
class InputHandler;
class WinState: public GameState
{
public:
	WinState();
	virtual ~WinState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	Texture* msg_;
	SDL_Rect dest_;
	InputHandler& ihdlr;
};

