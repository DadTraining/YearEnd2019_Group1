

#ifndef __MAPGAME_SCENE_H__
#define __MAPGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class MapGame : public cocos2d::Scene
{
public:
	float countT = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(FLOAT deltaTime);

	
      CREATE_FUNC(MapGame);
};

#endif // __MAPGAMEs_SCENE_H__
