// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include "../utils/Singleton.h"
#include <string>

class LittleWolf;
class Networking;

class Game: public Singleton<Game> {
	friend Singleton < Game>;
public:
	Game();
	virtual ~Game();
	bool init(char* host,Uint16 port);
	void start();

	LittleWolf& get_littlewolf() {
		return *little_wolf_;
	}

	Networking& get_networking() {
		return *net_;
	}


	void string_to_chars(std::string& str, char c_str[11]);
	void chars_to_string(std::string& str, char c_str[11]);
private:
	LittleWolf *little_wolf_;

	Networking* net_;

};

