#include "MainCharactor.h"



void MainCharactor::Right()
{
}

void MainCharactor::Push()
{
	if (this->GetSprite()->getNumberOfRunningActions() == 0) {
		auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetActionPushById(0), 0.2f);
		animate = Animate::create(animation);
		animate->setTag(11);
		this->GetSprite()->runAction(RepeatForever::create(animate));// goi nhieu lan???

	}
}

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
	this->SetSprite(Sprite::create());
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 200);
	this->scene->addChild(this->GetSprite());             // add child truoc

	action = PUSH;
}

void MainCharactor::Update(float deltaTime)
{
	switch (action)
	{
	case UP: {
		//
		break;
	}
	case DOWN: {
		//
		break;
	}
	case LEFT: {
		//
		break;
	}
	case RIGHT: {
		//
		break;
	}
	case PUSH: {
		Push();
		break;
	}
	case WAIT: {
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

