// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "netwrok_messages.h"

#include "LittleWolf.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return clientId_;
	}

	bool is_master() {
		return clientId_ == masterId_;
	}

	void send_state(LittleWolf::Line fov, LittleWolf::Point where, LittleWolf::Point velocity,
		float speed, float acceleration, float theta, int puntuation, int life/* LittleWolf::PlayerState state*/);
	void send_my_info(LittleWolf::Line fov, LittleWolf::Point where, LittleWolf::Point velocity,
		float speed, float acceleration, float theta, LittleWolf::PlayerState state, std::string name);
	
	void send_shoot(Uint8 pid);
	void send_dead(Uint8 id, Uint8 killerId,int damage);
	void send_restart();

private:

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_info(const PlayerInfoMsg &m);
	void handle_shoot(const ShootMsg &m);
	void handle_dead(const DeadMsg &m);
	void handle_restart();

	UDPsocket sock_;
	SDLNet_SocketSet socketSet_;
	UDPpacket *p_;
	IPaddress srvadd_;
	Uint8 clientId_;
	Uint8 masterId_;
};

