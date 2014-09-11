//
//  Player.cpp
//  Brave
//
//  Created by jack on 9/10/14.
//
//

#include "Player.h"

bool Player::initWithPlayerType(PlayerType type){
    // 主角的walk,attack,dead,hit,skill動作幀數
    int animationFrameNum[5]     = {4, 4, 4, 2, 4};

    // enemy1的walk,attack,dead,hit動作幀數
    int animationFrameNum2[5]    = {3, 3, 3, 2, 0};

    // 動作類型
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};

    std::string spName = "";
    
    _type = type;
    
    switch(type){
        case PLAYER:
            spName        = "player1-1-1.png";
            _name         = "player1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
            break;
        case ENEMY1:
            spName        = "enemy1-1-1.png";
            _name         = "enemy1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case ENEMY2:
            spName        = "enemy2-1-1.png";
            _name         = "enemy2";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    
    this->initWithSpriteFrameName(spName);
	_animationNames.assign(animationNames, animationNames + 5);
    
    this->addAnimation();
    
    return true;
}

void Player::addAnimation(){
    auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _name.c_str(), _animationNames[0].c_str())->getCString());
    
    if(animation)
        return;
    
    for (int i=0; i<_animationNum; i++) {
        auto animation = Animation::create();
        animation->setDelayPerUnit(0.2f);
        for (int j = 0; j<_animationFrameNum[i]; j++) {
            auto sfName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i+1, j+1)->getCString();
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
        }
        AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s", _name.c_str(), _animationNames[i].c_str())->getCString());
    }
}

void Player::playAnimationForever(int index){
    if(index < 0 || index >= _animationNum){
        log("illegal animation index!");
        return;
    }
    auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[index].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    this->runAction(RepeatForever::create(animate));
}

Player* Player::create(PlayerType type){
    Player* player = new Player();
    if(player && player->initWithPlayerType(type)){
        player->autorelease();
        return player;
    }else{
        delete player;
        player = NULL;
        return NULL;
    }
}