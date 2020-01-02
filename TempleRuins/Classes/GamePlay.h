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
	bool stun;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;

	Objject* main_charactor;
	Objject* spider;
	Objject* diamond;
	Objject* rock;

	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;

	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;

	cocos2d::Point mCurrentTouchPoint;
	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;
public:
	static Scene* createGame();
	virtual bool init();
	void CreateMap();
	void InitialState();
	void InitialObject();
	void AddDispatcher();
	void InitialButton();
	void InitialPhysics();
	bool OnContactBegin(PhysicsContact &contact);
	bool CheckFight();
	bool CheckPush();
	void CreateBloodBar();

	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	void update(float deltaTime);

	//
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);

	void EnablePressedControl(bool isLeft, bool pressed);

	void MoveLeft();

	void MoveRight();

	void UpdateController();
	//
	
	void setViewPointCenter(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);


	void AddDiamond();

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();

	void UpdateJoystick(float deltaTime);
};
