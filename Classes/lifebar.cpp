#include "lifebar.h"

using namespace std;
using namespace cocos2d;

LifeBar::LifeBar(int _life)
{
	lifeMax = _life;
	life = _life;
	bar = ProgressTimer::create(Sprite::create("life.png"));
	bar->setType(ProgressTimer::Type::BAR);
	bar->setBarChangeRate(Vec2(1, 0));
	bar->setMidpoint(Vec2(0, 0.5f));
	bar->setPercentage(100);
}

void LifeBar::updateLife(int dammage)
{
	life -= dammage;
	bar->setPercentage(life / lifeMax * 100);
}

void LifeBar::setLife(int _life) {
	lifeMax = _life;
	life = _life;
}
