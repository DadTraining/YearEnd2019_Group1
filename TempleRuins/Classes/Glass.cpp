#include "Glass.h"



void Glass::Init()
{
	// sprite
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(4)));
	this->GetSprite()->retain();
	this->GetSprite()->setAnchorPoint(Vec2(0, 0));
	this->GetSprite()->setScale(0.15);
	this->layer->addChild(this->GetSprite());
	this->GetSprite()->setTag(80);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
}

void Glass::Update(float deltaTime)
{
}

Glass::Glass(Layer* layer)
{
	this->layer = layer;
	Init();
}

Sprite * Glass::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}


Glass::~Glass()
{
	//delete this;
}
