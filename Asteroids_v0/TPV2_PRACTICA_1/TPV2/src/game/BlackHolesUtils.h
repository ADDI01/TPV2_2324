#pragma once
#include "BlackHolesFacade.h"

class Vector2D;
class RandomNumberGenerator;

class BlackHolesUtils: public BlackHolesFacade
{
public:
	BlackHolesUtils();
	virtual ~BlackHolesUtils(); 
	virtual void create_blackHoles(int n);
	virtual void remove_all_blackHoles();

private:

	void generateBlackHoles(const Vector2D& p, const Vector2D& v, int g);
	RandomNumberGenerator& rand_;
	int width_;
	int height_;
};

