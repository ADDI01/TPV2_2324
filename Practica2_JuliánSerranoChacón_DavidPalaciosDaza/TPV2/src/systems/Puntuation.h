// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class PuntuatuionSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PUNTUATIONSYSTEM)

		PuntuatuionSystem();
	virtual ~PuntuatuionSystem();

	inline auto getScore() {
		return score_;
	}

	inline void setScore(unsigned int score) {
		score_ = score;
	}

	inline void incrScore(unsigned int n) {
		score_ += n;
	}

	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;

private:
	unsigned int score_;
};

