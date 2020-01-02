#pragma once
#include "cocos2d.h"

USING_NS_CC;
class FightHammer
{
private:
	Sprite* sprite;
	PhysicsBody* physic;
public:
	Sprite* getFrameFight();
	Sprite* clone(Sprite* sprite);
	FightHammer();
	~FightHammer();
};

