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
	auto diamond = Sprite::create();
	Vector<SpriteFrame*> diamondVector;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Diamond/Diamond.plist", "Diamond/Diamond.png");
	diamondVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1_03.png"));
	diamond->retain();
	this->SetSprite(diamond);
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 200);
	this->scene->addChild(this->GetSprite());
}
void Diamond::Update(float deltaTime) 
{
}