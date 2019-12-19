#pragma once
#include "C:\Users\Admin\Desktop\2019\YearEnd2019_Group1\TempleRuins\cocos2d\cocos\2d\CCScene.h"
#include "MainCharactor.h"

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

