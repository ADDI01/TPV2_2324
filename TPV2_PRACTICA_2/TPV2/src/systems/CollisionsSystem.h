// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Transform;

class CollisionsSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::COLLISIONSSYSTEM)

	CollisionsSystem();
	virtual ~CollisionsSystem();
	void initSystem() override;
	void update() override;

	void checkCollisionsPacmanAndWalls(Transform& pacman);

};

