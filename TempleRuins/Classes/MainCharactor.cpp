#include "MainCharactor.h"



void MainCharactor::Right()
{
}

void MainCharactor::Push()
{
	this->GetSprite()->runAction(ResourceManager::GetInstance()->GetActionPushById(0));
	this->GetSprite()->setPosition(200, 200);
	this->scene->addChild(this->GetSprite());
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

