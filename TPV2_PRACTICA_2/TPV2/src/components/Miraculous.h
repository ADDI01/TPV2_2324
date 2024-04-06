#pragma once

#include <cassert>

#include "../ecs/Component.h"

class Texture;

class Miraculous : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::MIRACULOUS)

	Miraculous();
	virtual ~Miraculous();
	void initComponent() override;
	void render() override;

	void setMiracolousity(bool mir) { isMiraculous = mir; };

private:
	bool isMiraculous;
};
