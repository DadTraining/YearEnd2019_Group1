#include "Rock.h"



void Rock::Init()
{
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(2)));
	this->GetSprite()->setScale(SCALE_OBJECT);
	auto physicsBody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicsBody->setDynamic(true);
	this->GetSprite()->setPosition(200, 200);
	this->GetSprite()->setPhysicsBody(physicsBody);
	this->layer->addChild(this->GetSprite());
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
