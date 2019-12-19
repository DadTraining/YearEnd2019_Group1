#pragma once

#include "Objject.h"
#include "Item_game.h"
#include "CountTimer.h"
#include "MainCharactor.h"
#include "Rock.h"
#include "Spider.h"

#define NUM_ITEM 10
#define TIME_REMAIN 30
using namespace cocos2d;
class MiniGame : public Scene
{
private:
	bool push;
	bool fight;
	bool wait;
	bool run;
	bool stun;

	bool moveLeft;
	bool moveRight;
	vector<Objject* > items;
	CCPoint touch;
	int collect;
	Label* label_Collect;
	Sprite* timeRemain;
	Objject* countTimmer; //
	Objject* main_charac;  //
	Objject* spider; //
public:
	static Scene* createMiniGame();
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchEnded(Touch* touch, Event* event);
	bool onTouchMoved(Touch* touch, Event* event);
	MiniGame();
	~MiniGame();

	
	bool OnTouhBegan(Touch* touch, Event* event);
	void OnKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void update(float deltaTime);
	CREATE_FUNC(MiniGame);
};

