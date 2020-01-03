#include "FightHammer.h"



Sprite * FightHammer::getFrameFight()
{
	return this->sprite;
}

Sprite * FightHammer::clone(Sprite * sprite)
{
	return Sprite::createWithTexture(sprite->getTexture());
}

FightHammer::FightHammer()
{
	physic = PhysicsBody::createEdgeBox(Size(40.0f, 60.0f), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	physic->setRotationEnable(false);
	physic->setContactTestBitmask(1);
	this->sprite = clone(Sprite::create());
	sprite->setPhysicsBody(physic);
	sprite->retain();
	sprite->setTag(60);
}


FightHammer::~FightHammer()
{
}
