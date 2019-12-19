#pragma once
#include "2d\CCScene.h"
#include "cocos2d.h"
USING_NS_CC;
class GamePlayScene :
	public Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(GamePlayScene);

	GamePlayScene();
	~GamePlayScene();
};

