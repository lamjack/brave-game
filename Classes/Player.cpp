//
//  Player.cpp
//  Brave
//
//  Created by jack on 9/10/14.
//
//

#include "Player.h"

bool Player::initWithPlayerType(PlayerType type){
    std::string spName = "";
    _type = type;
    _speed = 100;
    _isShowBar = true;
    // 主角的walk,attack,dead,hit,skill動作幀數
    int animationFrameNum[5]     = {4, 4, 4, 2, 4};
    // enemy1的walk,attack,dead,hit動作幀數
    int animationFrameNum2[5]    = {3, 3, 3, 2, 0};
    
    switch(type){
        case PLAYER:
            spName = "player1-1-1.png";
            _name = "player1";
            _animationNum = 5;
            _isShowBar = false;
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
            _speed = 125;
            break;
        case ENEMY1:
            spName = "enemy1-1-1.png";
            _name = "enemy1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case ENEMY2:
            spName = "enemy2-1-1.png";
            _name = "enemy2";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    
    this->initWithSpriteFrameName(spName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
	_animationNames.assign(animationNames, animationNames + 5);
    
    this->addAnimation();
    
    this->initFSM();
    
    auto size = this->getContentSize();
    
    _progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
    _progress->setPosition(size.width * 2/3, size.height + _progress->getContentSize().height/2);
    this->addChild(_progress);
    if(!_isShowBar){
        _progress->setVisible(false);
    }
    
    return true;
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
    auto act = this->getActionByTag(index);
    
    if(act){
        return;
    }
    
    for (int i = 0; i < 5; i++) {
        this->stopActionByTag(i);
    }
    
    if(index < 0 || index >= _animationNum){
        log("illegal animation index!");
        return;
    }
    
    auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[index].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    animate->setTag(index);
    this->runAction(RepeatForever::create(animate));
}

void Player::walkTo(Vec2 dest){
    std::function<void()> onWalk = CC_CALLBACK_0(Player::onWalk, this, dest);
    _fsm->setOnEnter("walking", onWalk);
    _fsm->doEvent("walk");
}

void Player::initFSM(){
    _fsm = FSM::create("idle");
    
    // 增加一次引用次數
    _fsm->retain();
    
    auto onIdle = [&](){
        log("onIdle: Enter idle");
        this->stopActionByTag(0);
    };
    
    _fsm->setOnEnter("idle", onIdle);
}

void Player::onWalk(Vec2 dest){
    this->stopActionByTag(WALKTO_TAG);
    auto curPos = this->getPosition();
    
    // 如果現在目的位置在現在主角位置之後，則反轉
    if (curPos.x > dest.x) {
        this->setFlippedX(true);
    }else{
        this->setFlippedX(false);
    }
    
    auto diff = dest - curPos;
    auto time = diff.getLength()/_speed;
    auto move = MoveTo::create(time, dest);
    auto func = [&](){
        this->_fsm->doEvent("stop");
    };
    auto callback = CallFunc::create(func);
    auto seq = Sequence::create(move, callback, nullptr);
    seq->setTag(WALKTO_TAG);
    this->runAction(seq);
    this->playAnimationForever(0);
}

void Player::onExit(){
    Sprite::onExit();
    _fsm->release();
}