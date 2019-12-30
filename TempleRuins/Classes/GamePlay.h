#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "cocos2d.h"

USING_NS_CC;

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

	Objject* main_charactor;
public:
	static Scene* createGame();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	GamePlay();
	~GamePlay();
	CREATE_FUNC(GamePlay);
};

