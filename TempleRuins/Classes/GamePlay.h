#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"

#include "cocos2d.h"

using namespace cocos2d;


class GamePlay : public Scene
{
private:
	bool fight;

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool jump;

	SneakyJoystick *leftJoystick;
	SneakyButton *action1Button;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;

	Objject* main_charactor;
	Objject* spider;
public:
	static Scene* createGame();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	
	void setViewPointCenter(CCPoint position);
	

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();


	void UpdateJoystick(float deltaTime);
};

