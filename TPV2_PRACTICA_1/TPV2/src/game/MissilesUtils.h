#pragma once

#include "MissilesFacade.h"

class Vector2D;
class RandomNumberGenerator;

class MissilesUtils : public MissilesFacade
{
public:
    MissilesUtils();
    virtual ~MissilesUtils();
    void remove_all_missiles() override;
    void create_missiles(int n) override;

private:
    void generateBlackHoles(const Vector2D& p, const Vector2D& v, int g);
    RandomNumberGenerator& rand_;
    int width_;
    int height_;
};