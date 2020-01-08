#include "CountTimer.h"



void CountTimer::Init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// initial 
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetLoadById(0)));
	
	auto countTimer = ProgressTimer::create(this->GetSprite());
	countTimer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	countTimer->setScale(0.3);
	countTimer->setType(ProgressTimer::Type::RADIAL);
	countTimer->setPercentage(100);
	countTimer->setReverseProgress(true);
	countTimer->runAction(ProgressTo::create(timeRemain, 0));
	this->scene->addChild(countTimer);

	// initial timmer
	CCString* timer = CCString::createWithFormat("%i", timeRemain);
	label_Timer = Label::createWithTTF(timer->getCString(), "fonts/Marker Felt.ttf", 30);
	label_Timer->setPosition(countTimer->getPosition());
	this->scene->addChild(label_Timer);
}

void CountTimer::Update(float deltaTime)
{
	static float i = 0;
	i += deltaTime;
	if (i >= 1) {
		timeRemain--;
		i = 0;
	}

	CCString* timer = CCString::createWithFormat("%i", timeRemain);
	label_Timer->setString(timer->getCString());
}

Sprite * CountTimer::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

Size CountTimer::getSize()
{
	return Size();
}

CountTimer::CountTimer(Scene* scene, int timeRemain)
{
	this->timeRemain = timeRemain;
	this->scene = scene;
	Init();
}


CountTimer::~CountTimer()
{
}
