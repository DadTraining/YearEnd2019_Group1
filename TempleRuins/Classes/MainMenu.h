

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
	float countT = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
    
      CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
