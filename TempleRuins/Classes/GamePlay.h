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
	bool moveDown;
	bool jump;


	TMXTiledMap* map;
	TMXLayer* backgroundLayer;
	TMXLayer* wallLayer;
	TMXLayer* mPhysicsLayer;
	TMXObjectGroup* mObjectGroup;

	Objject* main_charactor;
	Objject* spider;

	void createMap();

	void createPhysics();

public:
	static Scene* createScene();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	
	void setViewPointCenter(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();


	void UpdateJoystick(float deltaTime);
};

