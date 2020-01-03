#pragma once
#include "2d\CCScene.h"
#include "2d\CCLayer.h"
#include "MainCharactor.h"
#include "Spider.h"
#include "Diamond.h"
#include "Rock.h"
#include "Glass.h"
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

	cocos2d::ui::Button *mFireController;
	cocos2d::ui::Button *mJumpController;

	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_wall;
	CCTMXLayer *_phy;

	Objject* main_charactor;
	Objject* rock;

	ui::LoadingBar *bloodBar_2;

	//
	cocos2d::EventKeyboard::KeyCode mCurrentKey;
	cocos2d::ui::Button *mBump;

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

	cocos2d::TMXObjectGroup* mObjectGroup;
	std::vector<Spider*> spiders;
	std::vector<Objject*> glasss;
	std::vector<Objject*> diamons;

public:
	static Scene *createGame();
	virtual bool init();
	void CreateMap();
	void InitialState();
	void InitialObject();
	void AddDispatcher();
	void InitialButton();
	void enablePressedControl(bool isLeft, bool pressed);
	void InitialPhysics();
	bool OnContactBegin(PhysicsContact &contact);
	//bool CheckFight();
	bool CheckPush();
	void CreateBloodBar();
	void CreateNumDiamon();
	void Fight(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void update(float deltaTime);

	//
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void EnablePressedControlLeftRight(bool isLeft, bool pressed);
	void EnablePressedControlUpDown(bool isUp, bool pressed);

	void UpdateController();
	//

	void setViewPointCenter(CCPoint position);
	CCPoint tileCoorforposition(CCPoint position);

	CREATE_FUNC(GamePlay);
	GamePlay();
	~GamePlay();
};
