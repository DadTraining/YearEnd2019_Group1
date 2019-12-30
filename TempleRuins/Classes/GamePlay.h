#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"

#include "cocos2d.h"

#define BLOOD_REDUCTION 5

using namespace cocos2d;

class GamePlay : public Layer
{
private:
	bool fight;
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool jump;

	TMXTiledMap *_tileMap;
	TMXLayer *backgroundLayer;
	TMXLayer *wallLayer;
	TMXLayer *mPhysicsLayer;
	TMXObjectGroup *mObjectGroup;

	Objject *main_charactor;
	Objject *spider;
	Objject *diamond;

	void createMap();

	void createPhysics();

public:
	static Scene *createGame();
	virtual bool init();
	void CreateMap();
	void InitialState();
	void InitialObject();
	void AddDispatcher();
	void InitialButton();
	void InitialPhysics();
	bool OnContactBegin(PhysicsContact &contact);
	bool CheckFight();
	void CreateBloodBar();

	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	void update(float deltaTime);

	void setViewPointCenter(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);


	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();

	void UpdateJoystick(float deltaTime);
};
