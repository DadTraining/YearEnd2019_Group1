#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CountTimer.h"

#define TIME_LOAD 3

class GameOver : public cocos2d::Scene
{
private:
	CountTimer* count;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback

	CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__