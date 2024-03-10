#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

class Transform;

class Rotation : public ecs::Component {
<<<<<<< Updated upstream
=======

	__CMPID_DECL__(ecs::cmp::TRANSFORM)

	Rotation() {}
	virtual ~Rotation() {}

	void initComponent();
	void update();

>>>>>>> Stashed changes
public:
	__CMPID_DECL__(ecs::cmp::ROTATION)

	Rotation():tr_() {};
	virtual ~Rotation() {};
	void initComponent();
	void update() override;

private:
	float rotation_;
	float actualRotation_;
	Transform* tr_;
};
