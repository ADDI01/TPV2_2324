// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>

#include "Game.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

Networking::Networking() :
		sock_(), //
		socketSet_(), //
		p_(), //
		srvadd_(), //
		clientId_(), //
		masterId_() {
}

Networking::~Networking() {
}

bool Networking::init(char *host, Uint16 port) {

	if (SDLNet_ResolveHost(&srvadd_, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sock_ = SDLNet_UDP_Open(0);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet_, sock_);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(p_->data);
					clientId_ = m1._client_id;
					masterId_ = m1._master_id;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int) clientId_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = clientId_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	MsgWithId m4;
	PlayerInfoMsg m5;
	DeadMsg m6;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			m1.deserialize(p_->data);
			masterId_ = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(p_->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			m5.deserialize(p_->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			m3.deserialize(p_->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			m6.deserialize(p_->data);
			handle_dead(m6);
			break;

		case _RESTART:
			handle_restart();
			break;

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != clientId_)
		Game::instance()->get_littlewolf().send_my_info();
}

void Networking::handle_disconnet(Uint8 id) {
	Game::instance()->get_littlewolf().removePlayer(id);
}

void Networking::send_state(LittleWolf::Line fov, LittleWolf::Point where, LittleWolf::Point velocity,
	float speed, float acceleration, float theta/*, LittleWolf::PlayerState state*/)
{

	PlayerStateMsg m;
	m._type = _PLAYER_STATE;
	m._client_id = clientId_;
	m.fax = fov.a.x;
	m.fay = fov.a.y;
	m.fbx = fov.b.x;
	m.fby = fov.b.y;
	m.wx = where.x;
	m.wy = where.y;
	m.vx = velocity.x;
	m.vy = velocity.y;
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	//m.state = state;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_state(const PlayerStateMsg &m) 
{

	if (m._client_id != clientId_) {
		LittleWolf::Line fov; fov.a.x = m.fax; fov.a.y = m.fay; fov.b.x = m.fbx; fov.b.y = m.fby;
		LittleWolf::Point w; w.x = m.wx; w.y = m.wy;
		LittleWolf::Point velocity; velocity.x = m.vx; velocity.y = m.vy;
		Game::instance()->get_littlewolf().update_player_state(m._client_id,fov,w,velocity,m.speed,m.acceleration,m.theta
			/*,(LittleWolf::PlayerState)m.state*/);
	}
}

void Networking::send_shoot(Uint8 pid) {
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = clientId_;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_shoot(const ShootMsg &m) {
	// play gun shot sound
	sdlutils().soundEffects().at("gunshot").play();

	if (is_master())
		Game::instance()->get_littlewolf().checkCollission(m._client_id);
}

void Networking::send_dead(Uint8 id) {
	DeadMsg m;
	m._type = _DEAD;
	m._client_id = clientId_;
	m.id = id;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_dead(const DeadMsg &m) {
	if (m._client_id != clientId_) {
		Game::instance()->get_littlewolf().killPlayer(m.id);
	}
}

void Networking::send_my_info(LittleWolf::Line fov, LittleWolf::Point where, LittleWolf::Point velocity,
	float speed,float acceleration,float theta, LittleWolf::PlayerState state)
{

	PlayerInfoMsg m;
	m._type = _PLAYER_INFO;
	m._client_id = clientId_;
	m.fax = fov.a.x;
	m.fay = fov.a.y;
	m.fbx = fov.b.x;
	m.fby = fov.b.y;
	m.wx = where.x;
	m.wy = where.y;
	m.vx = velocity.x;
	m.vy = velocity.y;
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_player_info(const PlayerInfoMsg &m) {
	if (m._client_id != clientId_) {
		LittleWolf::Line fov; fov.a.x = m.fax; fov.a.y = m.fay; fov.b.x = m.fbx; fov.b.y = m.fby;
		LittleWolf::Point w; w.x = m.wx; w.y = m.wy;
		LittleWolf::Point velocity; velocity.x = m.vx; velocity.y = m.vy;
		Game::instance()->get_littlewolf().update_player_info(m._client_id, fov, w, velocity, m.speed, m.acceleration, m.theta,
			(LittleWolf::PlayerState)m.state);
	}
}

void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::handle_restart() {
	Game::instance()->get_littlewolf().onRestart();
}
