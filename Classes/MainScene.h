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

class MainScene : public cocos2d::Layer{
    
public:
    CREATE_FUNC(MainScene);
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
    
};

#endif /* defined(__Brave__MainScene__) */
