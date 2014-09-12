//
//  MainScene.h
//  Brave
//
//  Created by jack on 9/11/14.
//
//

#ifndef __Brave__MainScene__
#define __Brave__MainScene__

#include "cocos2d.h"
#include "Player.h"
#include "VisibleRect.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer{
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MainScene);
    
    bool onTouchBegan(Touch* touch, Event* event);
    
private:
    Player* _player;
    Player* _enemy1;
    Player* _enemy2;
    Progress* _progress;
    EventListenerTouchOneByOne* _listenerTouch;
};

#endif /* defined(__Brave__MainScene__) */
