#include "Rotation.h"

#include "../ecs/Manager.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

void Rotation::initComponent()
{
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
	rotation_ = sdlutils().rand().nextInt(5, 10);
	actualRotation_ = tr_->getRot();
}

void Rotation::update()
{
	actualRotation_ += rotation_;
	tr_->setRot(actualRotation_);
}
