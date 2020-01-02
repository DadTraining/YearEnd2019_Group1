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
	bool jump;
	bool stun;
	bool moveUp;
	bool moveDown;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;

	Objject* main_charactor;
	Objject* spider;
	Objject* diamond;
	Objject* rock;

	ui::LoadingBar *bloodBar_2;

	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Button* mBump;

	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;

	cocos2d::Point mCurrentTouchPoint;
	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;
	cocos2d::Sprite* mMoveUpController;
	cocos2d::Sprite* mMoveUpControllerPressed;
	cocos2d::Sprite* mMoveDownController;
	cocos2d::Sprite* mMoveDownControllerPressed;

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
	bool CheckPush();
	void CreateBloodBar();
	void Fight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	void update(float deltaTime);

	//
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);

	void EnablePressedControlLeftRight(bool isLeft, bool pressed);
	void EnablePressedControlUpDown(bool isUp, bool pressed);

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
