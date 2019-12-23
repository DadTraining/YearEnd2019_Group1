#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "cocos2d.h"

using namespace cocos2d;

class GamePlay : public Scene
{
private:
	bool push;
	bool fight;
	bool wait;
	bool run;
	bool stun;

	bool moveLeft;
	bool moveRight;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;

	Objject* main_charactor;
public:
	static Scene* createMiniGame();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	
	void setViewPointCenter(CCPoint position);
	

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();
	
};

