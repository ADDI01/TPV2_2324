// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMANSYSTEM)

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	int update_lives(int l);
private:
	void createPacman();
	Transform *pmTR_;
};

