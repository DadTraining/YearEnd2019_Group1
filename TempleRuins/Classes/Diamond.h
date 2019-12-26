#pragma once
#include "Objject.h"

#define SCALE_SPRITE 0.3

class Diamond :
	public Objject
{
private:
	cocos2d::Scene* scene;
public:
	Diamond(cocos2d::Scene* scene);
	Sprite* Clone(cocos2d::Sprite* sprite);
	~Diamond();
	void Init();
	void Update(float deltaTime);
};

