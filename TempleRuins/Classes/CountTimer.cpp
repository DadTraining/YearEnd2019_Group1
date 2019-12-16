#include "CountTimer.h"



void CountTimer::Init()
{
	// initial 
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetLoadById(0)));
	auto countTimer = ProgressTimer::create(this->GetSprite());
	countTimer->setPosition(300,300);
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

CountTimer::CountTimer(Scene* scene, int timeRemain)
{
	this->timeRemain = timeRemain;
	this->scene = scene;
	Init();
}


CountTimer::~CountTimer()
{
}