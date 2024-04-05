#include "BlackHolesUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Rotation.h"
#include <math.h>

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
	//para elegir vía de spawn
	int wayToSpawn = rand_.nextInt(0, 2);

	//Desde dónde queremos emprezar (ángulo)
	float alpha = 90;
	//radio de los agujeros al fighter
	float r = rand_.nextInt(100, 300);
		switch (wayToSpawn)
		{
		case 0:
			for (int i = 0; i < n; i++)
			{
				//las probabilidades de dejar el programa colgado son nulas y que este bucle se repita más de una vez son
				// mínimas, esto evita que spawnee un agujero en el centro y les da un valor distinto a cada agujero
				do {
					x = rand_.nextInt(0, width_ - 408 * 0.1);
					y = rand_.nextInt(0, height_ - 341 * 0.1);
				} while (sqrt((x - width_ / 2) * (x - width_ / 2) +
					(y - height_ / 2) * (y - height_ / 2)) <= 200);

				generateBlackHoles(Vector2D(x, y));
			}

			break;
		case 1:
			for (int i = 0; i < n; i++) {
				x = r * cos((alpha) * (M_PI / 180.0));
				y = r * sin((alpha) * (M_PI / 180.0));
				alpha += 360.0 / n;
				generateBlackHoles(Vector2D(x + width_/2, y + height_/2));
			}
			break;
		default:
			break;
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
