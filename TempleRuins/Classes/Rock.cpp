#include "Rock.h"



void Rock::Init()
{
	auto rock = Clone(ResourceManager::GetInstance()->GetSpriteById(2));
	this->SetSprite(rock);
	rock->setScale(SCALE_OBJECT);

	auto physicsBody = PhysicsBody::createBox(rock->getContentSize());
	physicsBody->setDynamic(true);
	rock->setPosition(600, 200);
	rock->setPhysicsBody(physicsBody);
	
	this->GetSprite()->getPhysicsBody()->setContactTestBitmask(1);
	rock->setTag(50);
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


Rock::~Rock()
{
}
