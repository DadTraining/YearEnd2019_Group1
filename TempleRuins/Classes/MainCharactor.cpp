#include "MainCharactor.h"



MainCharactor::MainCharactor(Scene* scene)
{
	this->scene = scene;
	Init();
}

Sprite * MainCharactor::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}


MainCharactor::~MainCharactor()
{
}

void MainCharactor::Init()
{
	// create sprite
	this->SetSprite(Clone(Sprite::create()));
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 200);
	this->scene->addChild(this->GetSprite());   

	// create physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);

	// create animate
	// push
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorPush(), SPEED_FRAME);
	animate_push = Animate::create(animation);
	animate_push->retain();

	// wait
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorWait(), SPEED_FRAME);
	animate_wait = Animate::create(animation);
	animate_wait->retain();

	// run
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorRun(), SPEED_FRAME);
	animate_run = Animate::create(animation);
	animate_run->retain();

	Run();
	//action = C_PUSH;
}

void MainCharactor::Update(float deltaTime)
{
	switch (action)
	{
	case C_UP: {
		//
		break;
	}
	case C_DOWN: {
		//
		break;
	}
	case C_LEFT: {
		//
		break;
	}
	case C_RIGHT: {
		//
		break;
	}
	case C_PUSH: {
		this->GetSprite()->stopAllActions();
		Push();
		break;
	}
	case C_FIGHT: {
		//
		break;
	}
	case C_WAIT: {
		//
		break;
	}
	default:
		break;
	}
}

void MainCharactor::Up()
{
}

void MainCharactor::Down()
{
}

void MainCharactor::Left()
{
}

void MainCharactor::Right()
{
}

void MainCharactor::Push()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_push));
}

void MainCharactor::Fight()
{
}

void MainCharactor::Wait()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_wait));
}

void MainCharactor::Run()
{
	this->GetSprite()->runAction(RepeatForever::create(animate_run));
}
