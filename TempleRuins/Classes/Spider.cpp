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

	goDown();
}

void Spider::Update(float deltaTime)
{
	static bool check = true;
	static float i = 0;
	i += deltaTime;
	

	if (i >= 2) {
		check = !check;
	
		this->GetSprite()->stopAllActions();
		if (check) {
			goDown();
		}
		else {
			goUp();
		}

		i = 0;
	}
}

void Spider::goUp()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_up));
}

void Spider::goDown()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_down));
}

void Spider::goLeft()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_left));
}

void Spider::goRight()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_right));
}

Spider::Spider(Scene* scene)
{
	this->scene = scene;
	Init();
}


Spider::~Spider()
{
}
