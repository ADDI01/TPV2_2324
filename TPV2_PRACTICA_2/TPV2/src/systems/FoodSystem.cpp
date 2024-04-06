#include "FoodSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Miraculous.h"
#include "../components/ImageWithFrames.h"

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

		if (!foodMir->isMiraculous() && sdlutils().virtualTimer().currTime() >=
				foodMir->getTimeOfCreation() + foodMir->getMiraculousCD()) {
			ImageWithFrames* foodImg = mngr_->getComponent<ImageWithFrames>(food);

			foodImg->setNewFrame(1, 7, 1, 1);
			foodMir->setMiraculousity(true);
			foodMir.set
			foodMir->setMiraculousTimer(sdlutils().rand().nextInt(1, 6));
		}
		
		if(foodMir->isMiraculous() && sdlutils().virtualTimer().currTime() >= 
				)
	}
}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id)
	{case _m_NEW_GAME:
		generateGrid();
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

	mngr_->addComponent<Transform>(food, Vector2D(x, y ), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(food, &sdlutils().images().at("pacman_sprites"), 8, 8, 4, 0, 128, 
		128, 1, 4, 1, 1);
	mngr_->addComponent<Miraculous>(food, sdlutils().virtualTimer().currTime());
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
	mngr_->setAlive(food, false);
	nFoods--;
}
