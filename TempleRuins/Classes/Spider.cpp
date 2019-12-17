#include "Spider.h"



void Spider::Init()
{
	this->SetSprite(Sprite::create());
	this->GetSprite()->setPosition(300, 200);
	this->scene->addChild(this->GetSprite());

	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderDown(), 0.1f);
	animate = Animate::create(animation);
	this->GetSprite()->runAction(RepeatForever::create(animate));
}

void Spider::Update(float deltaTime)
{
	//this->GetSprite()->runAction(RepeatForever::create(animate));
	//this->GetSprite()->getActionByTag(1)->isDone(); // kiem tra
	//this->GetSprite()->stopAllActions(); //
}

Spider::Spider(Scene* scene)
{
	this->scene = scene;
	Init();
}


Spider::~Spider()
{
}
