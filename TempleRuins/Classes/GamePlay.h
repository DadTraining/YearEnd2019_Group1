#pragma once
#include "D:\gitclone\YearEnd2019_Group1\TempleRuins\cocos2d\cocos\2d\CCScene.h"
#include "MainCharactor.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"

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
	bool moveUp;
	bool moveDown;

	SneakyJoystick *leftJoystick;
	SneakyButton *action1Button;

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

	void UpdateJoystick(float deltaTime);

};

