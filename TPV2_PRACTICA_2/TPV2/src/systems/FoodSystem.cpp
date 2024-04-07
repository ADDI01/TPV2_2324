#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Miraculous.h"
#include "../components/ImageWithFrames.h"
#include "../components/Inmunity.h"

FoodSystem::FoodSystem()
{
}

FoodSystem::~FoodSystem()
{
}

void FoodSystem::initSystem()
{
}

void FoodSystem::update()
{
	std::vector<ecs::Entity*> foods = mngr_->getEntities(ecs::grp::FOODS);

	for (ecs::Entity* food : foods) {
		Miraculous* foodMir = mngr_->getComponent<Miraculous>(food);
		ImageWithFrames* foodImg = mngr_->getComponent<ImageWithFrames>(food);

		if (!foodMir->getIsMiraculous() && sdlutils().virtualTimer().currTime() >=
				foodMir->getTimeOfCreation() + foodMir->getMiraculousCD()) { //De estado normal a milagroso

			foodImg->setNewFrame(7, 1, 1, 1);
			foodMir->setMiraculousity(true);
			foodMir->setStartOfMiraculousTime(sdlutils().virtualTimer().currTime());
			foodMir->setMiraculousTimer(sdlutils().rand().nextInt(1000, 6000));
		}
		else if (foodMir->getIsMiraculous() && sdlutils().virtualTimer().currTime() >=
				foodMir->getStartOfMiraculousTime() + foodMir->getMiraculousRemaining()) { //De estado milagroso a normal

			foodImg->setNewFrame(4, 1, 1, 1);
			foodMir->setMiraculousity(false);
			foodMir->setTimeOfCreation(sdlutils().virtualTimer().currTime());
		}
	}
}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id)
	{case _m_NEW_GAME:
		generateGrid();
		break;
	case _m_ROUND_START:
		resetTimers();
		break;
	case _m_GAME_OVER:
		eatAllFoods();
		break;
	case _m_PACMAN_FOOD_COLLISION:
		eatFood(m.pacman_food_collision_data.food);
		if (nFoods == 0) {
			Message m2;
			m2.id = _m_GAME_OVER;
			m2.game_over_data.win = true;
			mngr_->send(m2);
		}
		break;
	default:
		break;
	}
}

void FoodSystem::resetTimers()
{
	std::vector<ecs::Entity*> foods = mngr_->getEntities(ecs::grp::FOODS);

	for (ecs::Entity* food : foods) {
		Miraculous* foodMir = mngr_->getComponent<Miraculous>(food);
		foodMir->setStartOfMiraculousTime(sdlutils().virtualTimer().currTime());
		foodMir->setTimeOfCreation(sdlutils().virtualTimer().currTime());
	}
}

void FoodSystem::generateGrid()
{
	int w = sdlutils().width();
	int h = sdlutils().height();
	int s = 35.0f;
	int offset = 35;
	for (float i = offset; i < w; i += w / cols) {
		for (float j = offset; j < h; j += h / rows) {
			createFood(i,j,s);
		}
	}
}

void FoodSystem::createFood(float x, float y, int s)
{
	ecs::Entity* food = mngr_->addEntity(ecs::grp::FOODS);
	bool miraculous = sdlutils().rand().nextInt(0, 10) == 0;
	mngr_->addComponent<Transform>(food, Vector2D(x, y ), Vector2D(), s, s, 0.0f);

	ImageWithFrames* foodImg = mngr_->addComponent<ImageWithFrames>(food, &sdlutils().images().at("pacman_sprites"), 8, 8, 4, 0, 128,
		128, 1, 4, 1, 1);

	mngr_->addComponent<Miraculous>(food, sdlutils().virtualTimer().currTime(), miraculous);
	if(miraculous)
		foodImg->setNewFrame(7, 1, 1, 1);
	nFoods++;
}

void FoodSystem::eatAllFoods()
{
	std::vector<ecs::Entity*> foods = mngr_->getEntities(ecs::grp::FOODS);
	nFoods = 0;
	for (ecs::Entity* food : foods)
		mngr_->setAlive(food, false);
}

void FoodSystem::eatFood(ecs::Entity* food)
{
	sdlutils().soundEffects().at("eat").play();
	Miraculous* foodMir = mngr_->getComponent<Miraculous>(food);
	if (!mngr_->getComponent<Inmunity>(mngr_->getHandler(ecs::hdlr::PACMAN))->getInmunnity() && foodMir->getIsMiraculous()) {
		Message m;
		m.id = _m_IMMUNITY_START;
		mngr_->send(m);
	}
	mngr_->setAlive(food, false);
	nFoods--;
}
