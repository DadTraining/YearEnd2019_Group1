#include "Spider.h"



void Spider::Init()
{
	// initial sprite
	this->SetSprite(Sprite::create());
	this->GetSprite()->setPosition(300, 200);
	this->scene->addChild(this->GetSprite());

	// action up
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderUp(), 0.1f);
	animate_up = Animate::create(animation);
	animate_up->setTag(actions_spider::GO_UP);
	animate_up->retain();

	// action down
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderDown(), 0.1f);
	animate_down = Animate::create(animation);
	animate_down->setTag(actions_spider::GO_DOWN);
	animate_down->retain();

	// action left
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderLeft(), 0.1f);
	animate_left = Animate::create(animation);
	animate_left->setTag(actions_spider::GO_LEFT);
	animate_left->retain();

	// action right
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderRight(), 0.1f);
	animate_right = Animate::create(animation);
	animate_right->setTag(actions_spider::GO_RIGHT);
	animate_right->retain();

	this->GetSprite()->runAction(RepeatForever::create(animate_up));
}

void Spider::Update(float deltaTime)
{
	static bool check = true;
	static float i = 0;
	i += deltaTime;
	

	if (i >= 1) {
		//check = !check;
		if (check) {
			this->GetSprite()->stopAllActions();
			check = false;
		}
		//this->SetSprite(Sprite::create());
		this->GetSprite()->runAction(RepeatForever::create(animate_down));    // action must retain()
		
		//if(this->GetSprite()->getNumberOfRunningActions() > 0) this->GetSprite();            // getsprite
		//if (check) {
		//	//this->GetSprite()->stopActionByTag(actions_spider::GO_UP);
		//	this->GetSprite()->runAction(RepeatForever::create(animate_down));
		//}
		//else {
		//	//this->GetSprite()->stopActionByTag(actions_spider::GO_DOWN);
		//	this->GetSprite()->runAction(RepeatForever::create(animate_up));
		//}

		//i = 0;
	}
}

void Spider::goUp()
{
	this->GetSprite()->runAction(animate_up);
}

void Spider::goDown()
{
	this->GetSprite()->runAction(animate_down);
}

void Spider::goLeft()
{
}

void Spider::goRight()
{
}

Spider::Spider(Scene* scene)
{
	this->scene = scene;
	Init();
}


Spider::~Spider()
{
}
