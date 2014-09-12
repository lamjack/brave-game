//
//  Progress.cpp
//  Brave
//
//  Created by jack on 9/12/14.
//
//

#include "Progress.h"

bool Progress::init(const char* background, const char* fillname){
    this->initWithSpriteFrameName(background);
    ProgressTimer* fill = ProgressTimer::create(Sprite::createWithSpriteFrameName(fillname));
    this->setFill(fill);
    this->addChild(fill);
    
    // 血條是條狀
    fill->setType(ProgressTimer::Type::BAR);
    // 起點為左側中間點
    fill->setMidpoint(Point(0, 0.5));
    // 變化率為x軸每次變化1，y軸不變
    fill->setBarChangeRate(Point(1.0, 0));
    // 填充率為100，即滿血
    fill->setPosition(this->getContentSize()/2);
    fill->setPercentage(100);
    
    return true;
}

Progress* Progress::create(const char* background, const char* fillname){
    Progress* progress = new Progress();
    if(progress && progress->init(background, fillname)){
        progress->autorelease();
        return progress;
    }else{
        delete progress;
        progress = NULL;
        return NULL;
    }
}