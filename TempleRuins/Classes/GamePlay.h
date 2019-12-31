#pragma once
#include "2d\CCScene.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"
#include "Rock.h"

#include "cocos2d.h"

#define BLOOD_REDUCTION 5

using namespace cocos2d;


class GamePlay : public Layer
{
private:
	bool fight;
	bool push;
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool jump;

	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;

	cocos2d::ui::Button* mFireController;
	cocos2d::ui::Button* mJumpController;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_frame;


	Objject* main_charactor;
	Objject* spider;
	Objject* diamond;
	Objject* rock;
public:
	static Scene* createGame();
	virtual bool init();
	void CreateMap();
	void InitialState();
	void InitialObject();
	void AddDispatcher();
	void InitialButton();
	void enablePressedControl(bool isLeft, bool pressed);
	void InitialPhysics();
	bool OnContactBegin(PhysicsContact& contact);
	bool CheckFight();
	bool CheckPush();
	void CreateBloodBar();

	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	
	void setViewPointCenter(CCPoint position);

	void AddDiamond();

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();

	void UpdateJoystick(float deltaTime);

};

