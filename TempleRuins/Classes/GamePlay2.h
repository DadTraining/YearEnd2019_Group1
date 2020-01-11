#pragma once
#include "2d\CCLayer.h"
#include "cocos2d.h"
#include "Objject.h"

USING_NS_CC;
class GamePlay2 :
	public Layer
{
private:
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	cocos2d::TMXObjectGroup* mObjectGroup;

public:
	GamePlay2();
	~GamePlay2();
	static Scene *createGame();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(GamePlay2);

	void createMap();
	void createMapPhysics();
	void createObject();
};

