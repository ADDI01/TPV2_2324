#pragma once

#include <cassert>

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

class Texture;

class Miraculous : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::MIRACULOUS)

	Miraculous(Uint32 time);
	virtual ~Miraculous();
	bool getIsMiraculous() const { return isMiraculous; }
	Uint32 getTimeOfCreation() const { return timeOfCreation; }
	float getMiraculousCD() const { return miraculousCD; }
	float getMiraculousRemaining() const { return miraculousRemaining; }

	void setMiraculousity(bool mir);
	void setTimeOfCreation(Uint32 time);
	void setMiraculousTimer(float mirTm);
	void setStartOfMiraculousTime(float startMrTm);

private:
	bool isMiraculous_; //Si es o no milagrosa
	Uint32 timeOfCreation; //Guarda el momento en el que se creo la fruta
	Uint32 startOfMiraculousTime; //Momento que empieza a ser milagrosa
	float miraculousCD; //Tiempo  hasta hacerse milagrosa
	float miraculousRemaining; //Duracion del estado milagroso
};