#pragma once

#include "../ecs/System.h"

struct Transform;

class ImmunitySystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::INMUNITYSYSTEM)

		ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	virtual void recieve(const Message& m);

private:
	int startInmunityTime;
};

