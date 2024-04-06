#pragma once

#include <cassert>

#include "../ecs/Component.h"

class Texture;

class Inmunity : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::INMUNITY)

	Inmunity();
	virtual ~Inmunity();
	void setInmunity(bool inm) { isInmune = inm; }

private:
	bool isInmune;
};

