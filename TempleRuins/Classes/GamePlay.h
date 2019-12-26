#pragma once
#include "C:\Users\Admin\Desktop\2019\YearEnd2019_Group1\TempleRuins\cocos2d\cocos\2d\CCScene.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"

class GamePlay : public Scene
{
private:
	bool fight;

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool jump;

	SneakyJoystick *leftJoystick;
	SneakyButton *action1Button;

	Objject* main_charactor;
	Objject* spider;
public:
	static Scene* createGame();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	GamePlay();
	~GamePlay();
	CREATE_FUNC(GamePlay);


	void UpdateJoystick(float deltaTime);
};

