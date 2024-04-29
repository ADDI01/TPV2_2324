#pragma once
#include "../ecs/Component.h"
class Transform;

class MarginsCollision: public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::MARGINSCOLLISION)
	MarginsCollision() {};
	virtual ~MarginsCollision() {};
	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
};

