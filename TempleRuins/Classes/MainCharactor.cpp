#include "MainCharactor.h"



MainCharactor::MainCharactor(Scene* scene)
{
	this->scene = scene;
}


MainCharactor::~MainCharactor()
{
}

void MainCharactor::Init()
{
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
		//
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

