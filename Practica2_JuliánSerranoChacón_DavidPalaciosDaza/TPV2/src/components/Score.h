#pragma once

#include <cassert>

#include "../ecs/Component.h"

const int GHOST_POINTS = 20;

class Score : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::SCORE)

	Score();
	virtual ~Score();
	int getScore() const { return score_; }
	void setScore(int score) { score_ += score; }

private:
	int score_;
};

