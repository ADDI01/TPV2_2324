#pragma once

#include "../ecs/System.h"

struct Transform;

class ImmunitySystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::GHOSTSYSTEM)

		ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	virtual void recieve(const Message& m);

private:
	Uint32 startInmunityTime;
};

