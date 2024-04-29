#include "LookAt.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include <cassert>
LookAt::LookAt(): tr_(nullptr){
}

void LookAt::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void LookAt::update() {
	tr_->setRot(Vector2D(0, -1).angle(tr_->getVel()));
}