#pragma once
#include "2d\CCLayer.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"
#include "Rock.h"
#include "Glass.h"
#include "MainMenu.h"
#include "MapGame.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

class GamePlay : 
	public Layer
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

	// button
	cocos2d::ui::Button *mFireController;
	cocos2d::ui::Button *mJumpController;

	// map
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;
	CCTMXLayer *_thang;

	// thang
	vector<Vec2> _thang_Pos;

	
	float distance_1(float p_1, float p_2);

	// collision 2
	void checkGround_2();
	cocos2d::TMXObjectGroup* mObjects_line_down;
	cocos2d::TMXObjectGroup* mObjects_line_up;
	vector<Vec2> _Line_Down_Pos;
	vector<Vec2> _Line_Down_Pos_2;
	vector<Vec2> _Line_Down_Pos_3;
	vector<Vec2> _Line_Down_Pos_4;
	vector<Vec2> _Line_Down_Pos_5;
	vector<Vec2> _Line_Down_Pos_6;
	vector<Vec2> _Line_Up_Pos_1;
	vector<Vec2> _Line_Up_Pos_2;
	vector<Vec2> _Line_Up_Pos_3;
	vector<Vec2> _Line_Up_Pos_4;
	vector<Vec2> _Line_Up_Pos_5;
	vector<Vec2> _Line_Up_Pos_6;


	// main charactor
	Objject* main_charactor;
	ui::LoadingBar *bloodBar_1;
	ui::LoadingBar *bloodBar_2;
	int SPEED_CHARACTOR_RUN = 5;


	// state key
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;
	cocos2d::Point mCurrentTouchPoint;

	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;

	// object map
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
	bool check_Collision(int index);
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
