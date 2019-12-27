#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"

#include "cocos2d.h"

using namespace cocos2d;


class GamePlay : public Scene
{
private:
	bool fight;

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool jump;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;

	Objject* main_charactor;
	Objject* spider;
	Objject* diamond;
public:
	static Scene* createGame();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	
	void setViewPointCenter(CCPoint position);

	void AddDiamond();

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();

	void UpdateJoystick(float deltaTime);

	bool onContactBegin(PhysicsContact & contact);

};

