#include "MissilesUtils.h"

#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/Image.h"
#include "../components/Transform.h"

MissilesUtils::MissilesUtils():rand_(sdlutils().rand()), width_(sdlutils().width()), height_(sdlutils().height())
{
}

MissilesUtils::~MissilesUtils()
{
}

void MissilesUtils::remove_all_missiles()
{
}

void MissilesUtils::create_missiles(int n)
{
}

void MissilesUtils::generateBlackHoles(const Vector2D& p, const Vector2D& v, int g)
{
}
