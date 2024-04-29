#include "MissilesUtils.h"

#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/LookAt.h"
#include "../components/MarginsCollision.h"
#include "Game.h"
#include "../ecs/Manager.h"

MissilesUtils::MissilesUtils():rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height())
{
}

MissilesUtils::~MissilesUtils()
{
}

void MissilesUtils::remove_all_missiles()
{
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void MissilesUtils::create_missiles(int n)
{
	for (int i = 0; i < n; i++)
		generateMissiles();
}

void MissilesUtils::generateMissiles()
{
	auto mngr = Game::instance()->getMngr();
	auto image = &sdlutils().images().at("missle");
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto e = mngr->addEntity(ecs::grp::MISSILES);
	Vector2D p;
	int chooseP = rand_.nextInt(0, 4);
	switch (chooseP)
	{
	case 0:
		p = Vector2D(0, 0);
		break;
	case 1:
		p = Vector2D(width_ - image->width()* 0.1, 0);
		break;
	case 2:
		p = Vector2D(0, height_ - image->height() * 0.1);
		break;
	case 3:
		p = Vector2D(width_ - image->width() * 0.1, height_ - image->height() * 0.1);
		break;
	default:
		break;
	}


	Vector2D c = Vector2D(width_ / 2 + rand_.nextInt(-100, 100),
		height_ / 2 + rand_.nextInt(-100, 100));

	Vector2D v = (c - p).normalize() * (rand_.nextInt(1, 4) / 3.0);

	mngr->addComponent<Transform>(e, p, v, image->width() * 0.1, image->height() * 0.1, Vector2D(0, -1).angle(v));
	mngr->addComponent<Image>(e, image);
	mngr->addComponent<Follow>(e, mngr->getComponent<Transform>(fighter)->getPos());
	mngr->addComponent<LookAt>(e);
	mngr->addComponent<MarginsCollision>(e);
}
