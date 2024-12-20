// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "BlackHolesFacade.h"
#include <math.h>
#include "MissilesFacade.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, BlackHolesFacade * blackHoles_mngr, MissilesFacade* missiles_mngr) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr), //
	    blackHoles_mngr_(blackHoles_mngr),
		lastTimeGeneratedAsteroids_(),
		missiles_mngr_(missiles_mngr){
} 

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACKHOLES);
	auto &missiles = mngr->getEntities(ecs::grp::MISSILES);
	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}
	for (auto b : blackHoles) {
		mngr->update(b);
	}
	for (auto m : missiles) {
		mngr->update(m);
	}
	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : blackHoles) {
		mngr->render(a);
	}
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto m : missiles) {
		mngr->render(m);
	}
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedMissiles_ + 15000) {
		missiles_mngr_->create_missiles(1);
		lastTimeGeneratedMissiles_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACKHOLES);
	auto &missiles = mngr->getEntities(ecs::grp::MISSILES);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto num_of_asteroids = asteroids.size();
	auto num_of_blackHoles = blackHoles.size();
	auto num_of_missiles = missiles.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

	}

	for (auto i = 0u; i < num_of_blackHoles; i++) {
		auto b = blackHoles[i];
		if (!mngr->isAlive(b))
			continue;

		// asteroid with fighter
		auto bTR = mngr->getComponent<Transform>(b);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			bTR->getPos(), //
			bTR->getWidth(), //
			bTR->getHeight(), //
			bTR->getRot())) {
			onFigherDeath();
			return;
		}

		for (auto ast : asteroids) {
			Transform* astT = mngr->getComponent<Transform>(ast);
			if (Collisions::collidesWithRotation( //
				astT->getPos(), //
				astT->getWidth(), //
				astT->getHeight(), //
				astT->getRot(), //
				bTR->getPos(), //
				bTR->getWidth(), //
				bTR->getHeight(), //
				bTR->getRot())) {
				float x;
				float y;
				//las probabilidades de dejar el programa colgado son nulas y que este bucle se repita m�s de una vez son
				// m�nimas, esto evita que spawnee un asteroide encima del caza y les da un valor distinto a cada agujero
				do {
					 x = sdlutils().rand().nextInt(astT->getWidth(), sdlutils().width() - astT->getWidth());
					 y = sdlutils().rand().nextInt(astT->getHeight(), sdlutils().height() - astT->getHeight());
				} while (sqrt((x - fighterTR->getPos().getX()) * (x - fighterTR->getPos().getX()) +
					(y - fighterTR->getPos().getY()) * (y - fighterTR->getPos().getY())) <= 200);
				astT->setPos((Vector2D(x, y)));
				return;
			}
		}
	}

	for (auto i = 0u; i < num_of_missiles; i++) {
		auto m = missiles[i];
		if (!mngr->isAlive(m))
			continue;

		auto mTR = mngr->getComponent<Transform>(m);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			mTR->getPos(), //
			mTR->getWidth(), //
			mTR->getHeight(), //
			mTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
					b.pos, //
					b.width, //
					b.height, //
					b.rot, //
					mTR->getPos(), //
					mTR->getWidth(), //
					mTR->getHeight(), //
					mTR->getRot())) {
					mngr->setAlive(m, false);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

	}

}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
