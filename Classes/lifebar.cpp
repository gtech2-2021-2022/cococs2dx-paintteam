#include "lifebar.h"

using namespace std;
using namespace cocos2d;

LifeBar::LifeBar(int _life)
{
	lifeMax = _life;
	life = _life;
	bar = ui::LoadingBar::create("life.png");
}

void LifeBar::updateLife(int dammage)
{
	life -= dammage;
	bar->setPercent(life / lifeMax * 100);
}
