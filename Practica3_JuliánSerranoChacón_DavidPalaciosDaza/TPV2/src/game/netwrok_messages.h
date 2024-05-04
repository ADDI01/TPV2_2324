// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"

enum MsgType : Uint8 {
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECTED,
	_NEW_CLIENT_CONNECTED, //
	_PLAYER_STATE, //
	_PLAYER_INFO, //
	_SHOOT, //
	_DEAD, //
	_RESTART
};

struct Msg {
	Uint8 _type;

	_IMPL_SERIALIAZION_(_type)
};

struct MsgWithId: Msg {
	Uint8 _client_id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,_client_id)
};

struct MsgWithMasterId: MsgWithId {
	Uint8 _master_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,_master_id)
};

struct PlayerStateMsg: MsgWithId {
	float fax;            // focal view
	float fay;
	float fbx;
	float fby;

	float wx;         // current position (wrt. to the grid)
	float wy;

	float vx;      // current velocity
	float vy;

	float speed;         // maximum speed
	float acceleration;  // acceleration
	float theta;         // rotation (in rad)
	Uint8 state;   // the state

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, fax, fay, fbx, fby, wx, wy, vx, vy, speed, acceleration, theta, state)

};

struct PlayerInfoMsg: MsgWithId {
	float fax;            // focal view
	float fay;
	float fbx;
	float fby;

	float wx;         // current position (wrt. to the grid)
	float wy;

	float vx;      // current velocity
	float vy;

	float speed;         // maximum speed
	float acceleration;  // acceleration
	float theta;         // rotation (in rad)
	Uint8 state;   // the state

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, fax, fay, fbx, fby, wx, wy, vx, vy,speed,acceleration,theta,state)

};
struct ShootMsg: MsgWithId {
	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, )

};
struct DeadMsg : MsgWithId {
	Uint8 id;
	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, id)

};
