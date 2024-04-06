#pragma once

#include <cassert>

#include "../ecs/Component.h"

class Texture;

class Miraculous : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::MIRACULOUS)

	Miraculous();
	virtual ~Miraculous();

	void setMiraculousity(bool mir) { isMiraculous = mir; };

private:
	bool isMiraculous;
};
