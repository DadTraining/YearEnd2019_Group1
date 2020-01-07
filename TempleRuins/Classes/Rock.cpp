#include "Rock.h"

void Rock::Init()
{
	// sprite
	auto rock = Clone(ResourceManager::GetInstance()->GetSpriteById(2));
	this->SetSprite(rock);
	//rock->setScale(SCALE_ROCK);
	this->GetSprite()->setAnchorPoint(Vec2(0, 0));

	// physics
	auto physicsBody = PhysicsBody::createBox(rock->getContentSize());
	//auto physicsBody = PhysicsBody::createCircle
	physicsBody->setDynamic(true);
	physicsBody->setRotationEnable(false);
	physicsBody->setMass(100);
	rock->setPhysicsBody(physicsBody);
	
	// colission
	this->GetSprite()->getPhysicsBody()->setContactTestBitmask(1);
	rock->setTag(TAG_ROCK);
	this->layer->addChild(rock);
}

void Rock::Update(float deltaTime)
{
}

Rock::Rock(Layer* layer)
{
	this->layer = layer;
	Init();
}

Sprite * Rock::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

Size Rock::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_ROCK;
}


Rock::~Rock()
{
}
