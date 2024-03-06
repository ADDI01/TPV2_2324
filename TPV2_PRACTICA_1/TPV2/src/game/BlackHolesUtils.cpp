#include "BlackHolesUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"

BlackHolesUtils::BlackHolesUtils() : rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height())
{
}

BlackHolesUtils::~BlackHolesUtils()
{
}

void BlackHolesUtils::create_blackHoles(int n)
{

	for (int i = 0; i < n; i++) 
	{
		generateBlackHoles(Vector2D(100,100));
	}
}

void BlackHolesUtils::remove_all_blackHoles()
{
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::BLACKHOLES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void BlackHolesUtils::generateBlackHoles(const Vector2D& p)
{

	auto mngr = Game::instance()->getMngr();

	auto e = mngr->addEntity(ecs::grp::BLACKHOLES);
	mngr->addComponent<Transform>(e, p, Vector2D(0,0), 408 * 0.1, 341 * 0.1, 0.0f);
	mngr->addComponent<Image>(e, &sdlutils().images().at("black-hole"));
}
