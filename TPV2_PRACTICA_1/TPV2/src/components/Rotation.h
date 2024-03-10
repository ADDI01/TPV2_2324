#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

class Transform;

class Rotation : public ecs::Component {

	__CMPID_DECL__(ecs::cmp::TRANSFORM)

	Rotation() {}
	Rotation() {}
	virtual ~Rotation() {}

	void initComponent();
	void update();

public:
	float rotation_;
	float actualRotation_;
	Transform* tr_;
};
