#pragma once
#include "2d\CCScene.h"
#include "2d\CCLayer.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"
#include "Rock.h"
#include "Glass.h"
#include "MainMenu.h"
#include "cocos2d.h"

#define BLOOD_REDUCTION 5

//using namespace cocos2d;
USING_NS_CC;

class GamePlay : public Layer
{
private:
	int numDiamond;
	Label* LabelNumDiamon;

	bool fight;
	bool push;
	bool moveLeft;
	bool moveRight;
	bool jump;
	bool stun;
	bool moveUp;
	bool moveDown;
	bool fall;

	cocos2d::ui::Button *mFireController;
	cocos2d::ui::Button *mJumpController;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	CCTMXLayer *_thang;

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


	Objject* main_charactor;
	ui::LoadingBar *bloodBar_2;

	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	


	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;

	cocos2d::Point mCurrentTouchPoint;

	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;


	cocos2d::TMXObjectGroup* mObjectGroup;
	std::vector<Spider*> spiders;
	std::vector<Objject*> glasss;
	std::vector<Objject*> diamons;
	std::vector<Objject*> rocks;
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
	void CreateBloodBar();
	void CreateNumDiamon();
	void createPauseLayer();
	void Fight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void Jump(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void climb();
	void Pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	// push rock
	void push_rock();
	int check_push();
	float distance(float main, float rock);
	
	// update
	void update(float deltaTime);

	// touch
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);


	// key
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event);


	void EnablePressedControlLeftRight(bool isLeft, bool pressed);
	void EnablePressedControlUpDown(bool isUp, bool pressed);
	void UpdateController();

	void setViewPointCenter(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();
};
