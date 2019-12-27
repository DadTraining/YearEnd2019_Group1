#include "Diamond.h"



Diamond::Diamond(cocos2d::Scene* scene)
{
	this->scene = scene;
	this->Init();
}


Diamond::~Diamond()
{
}

Sprite* Diamond::Clone(cocos2d::Sprite* sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

void Diamond::Init()
{
	//create sprite
	auto diamond = Sprite::create("Diamond/1_03.png");
	diamond->retain();
	this->SetSprite(diamond);
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(100, 100);
	this->scene->addChild(this->GetSprite());

	//add physic
	auto physicsBody1 = PhysicsBody::createBox(diamond->getContentSize());
	physicsBody1->setDynamic(false);
	physicsBody1->setRotationEnable(false);
	diamond->setPhysicsBody(physicsBody1);
	diamond->getPhysicsBody()->setContactTestBitmask(1);

}
void Diamond::Update(float deltaTime) 
{
}