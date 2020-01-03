#pragma once
#include "Objject.h"

#define SCALE_SPRITE 0.6

class Diamond :
	public Objject
{
private:
	cocos2d::Layer* layer;
public:
	Diamond(cocos2d::Layer* layer);
	Sprite* Clone(cocos2d::Sprite* sprite);
	~Diamond();
	void Init();
	void Update(float deltaTime);
};

