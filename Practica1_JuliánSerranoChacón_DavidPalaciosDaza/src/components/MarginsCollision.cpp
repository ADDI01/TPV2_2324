#include "MarginsCollision.h"
#include "Transform.h"
#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"


void MarginsCollision::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void MarginsCollision::update() {
	if (tr_->getPos().getX() < 0 - tr_->getWidth() || tr_->getPos().getX() > sdlutils().width() + tr_->getWidth() ||
		tr_->getPos().getY() < 0 - tr_->getHeight() || tr_->getPos().getY() > sdlutils().height() + tr_->getHeight())
			mngr_->setAlive(ent_, false);
}