#include "BlackHolesUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Rotation.h"

BlackHolesUtils::BlackHolesUtils() : rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height())
{
}

BlackHolesUtils::~BlackHolesUtils()
{
}

void BlackHolesUtils::create_blackHoles(int n)
{
	float x;
	float y;

	for (int i = 0; i < 6; i++) 
	{
		//las probabilidades de dejar el programa colgado son nulas y que este bucle se repita más de una vez son
		// mínimas, esto evita que spawnee un agujero en el centro y les da un valor distinto a cada agujero
		do {
			x = rand_.nextInt(width_, sdlutils().width() - width_);
			y = rand_.nextInt(height_, sdlutils().height() - height_);
		} while (sqrt((x + sdlutils().width() / 2) * (x + sdlutils().width() / 2) +
			(y + sdlutils().height() / 2) * (y + sdlutils().height() / 2)) <= 200);
		generateBlackHoles(Vector2D(x,y));
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
	mngr->addComponent<Rotation>(e);
}
