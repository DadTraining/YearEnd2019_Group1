
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class LoadingLogo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void changeLoading(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingLogo);
};

#endif // __HELLOWORLD_SCENE_H__
