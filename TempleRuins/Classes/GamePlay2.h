#pragma once
#include "2d\CCLayer.h"
#include "cocos2d.h"
#include "Objject.h"
#include "MainCharactor.h"
#include "Rock.h"
#include "Glass.h"
#include "Diamond.h"
#include "Spider.h"
#include "MapGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class GamePlay2 :
	public Layer
{
private:
	//Object
	Objject* main_charactor;
	std::vector<Spider*> spiders;
	std::vector<Objject*> glasss;
	std::vector<Objject*> diamons;
	std::vector<Objject*> rocks;
	
	//State Move of Charactor
	bool moveLeft;
	bool moveRight;
	bool jump;
	bool moveUp;
	bool moveDown;

	//State Action of Charactor
	bool fight;
	bool push;
	bool stun;
	bool fall;

	//Map
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	cocos2d::TMXObjectGroup* mObjectGroup;

	//Button
	cocos2d::ui::Button *mFireController;
	cocos2d::ui::Button *mJumpController;

	//Button move left + move right
	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;
	
	//Header bar
	int numDiamond2;
	Label* LabelNumDiamon;
	ui::LoadingBar *bloodBar;
	
	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	cocos2d::Point mCurrentTouchPoint;

	Vec2 _thang_1;
	Vec2 _thang_2;

	/////////// test ground not physic
	Vec2 _ground_Pos;
	Vec2 _ground_Pos_1;
	Vec2 _ground_Pos_2;
	void checkGround();
	bool _collistionGround = false;
	float distance_1(float p_1, float p_2);

	//////////////////////////////// test tiep
	Vec2 _ground_Pos_12;
	Vec2 _ground_Pos_13;
	Vec2 _ground_Pos_14;
	Vec2 _ground_Pos_15;
	Vec2 _ground_Pos_16;
	Vec2 _ground_Pos_17;
	Vec2 _ground_Pos_18;
	Vec2 _ground_Pos_19;
	Vec2 _ground_Pos_20;
	Vec2 _ground_Pos_21;
	Vec2 _ground_Pos_22;
	Vec2 _ground_Pos_23;
	Vec2 _ground_Pos_24;

public:
	GamePlay2();
	~GamePlay2();

	static Scene *createGame();
	virtual bool init();
	// update
	void update(float deltaTime);
	CREATE_FUNC(GamePlay2);

	void createMap();
	void createMapPhysics();
	void createObject();
	void InitialState();
	void AddDispatcher();
	void setViewPointCenter(CCPoint position);
	void EnablePressedControlLeftRight(bool isLeft, bool pressed);
	void UpdateController();
	void push_rock();
	int check_push();
	float distance(float main, float rock);
	bool OnContactBegin(PhysicsContact &contact);
	void CreateBloodBar();
	void CreateNumDiamon();
	void createPauseLayer();
	void Fight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void Jump(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void climb();
	void Pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void InitialButton();


	// touch
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	
	//key
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
};

