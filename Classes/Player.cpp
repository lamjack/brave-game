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
    int animationFrameNum[5] ={4, 4, 4, 2, 4};
    int animationFrameNum2[5] ={3, 3, 3, 2, 0};
    
    switch(type){
        case PLAYER:
            spName = "player1-1-1.png";
            _name = "player1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
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
    
    return true;
}

void Player::addAnimation(){
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