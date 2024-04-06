#pragma once

#include "../ecs/System.h"
class FoodSystem: public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FOODSYSTEM)

	FoodSystem();
	virtual ~FoodSystem();
	void initSystem() override;
	void update() override;
	virtual void recieve(const Message& m);
private:
	void generateGrid();
	void createFood(float x, float y, int s);
	const int cols = 8;
	const int rows = 6;
	int nFoods = 0;
};

