// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"

class LittleWolf;

class Game : public Singleton<Game> {
public:
	friend Singleton<Game>;
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	LittleWolf *little_wolf_;

};

