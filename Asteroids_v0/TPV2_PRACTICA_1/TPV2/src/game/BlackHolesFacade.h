#pragma once

class BlackHolesFacade {
public:
	BlackHolesFacade() {};
	virtual ~BlackHolesFacade() {};
	virtual void create_blackHoles(int n) = 0;
	virtual void remove_all_blackHoles() = 0;
};