#pragma once

#include "../ecs/System.h"

struct Transform;

class GhostSystem:  public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::GHOSTSYSTEM)

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	int update_lives(int l);
	void createGhost();
	virtual void recieve(const Message& m);
	void onGhostDie(ecs::Entity* ghostDead);
private:
	int nGhosts;
};

