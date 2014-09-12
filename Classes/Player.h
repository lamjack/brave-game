//
//  Player.h
//  Brave
//
//  Created by jack on 9/10/14.
//
//

#ifndef __Brave__Player__
#define __Brave__Player__

#include <cocos2d.h>
#include "FSM.h"
#include "Progress.h"
USING_NS_CC;

class Player : public Sprite{

public:
	enum PlayerType{
		PLAYER,
		ENEMY1,
		ENEMY2
	};
    
    enum ActionTag{
        WALKTO_TAG = 100
    };
    
    enum AnimationType{
        WALKING = 0,
        ATTACKING,
        DEAD,
        BEINGHIT,
        SKILL
    };
    
    bool initWithPlayerType(PlayerType type);
    
    static Player* create(PlayerType type);
    
    void addAnimation();
    
    void playAnimationForever(int index);
    
    void walkTo(Vec2 dest);
    
    void initFSM();
    
    void onWalk(Vec2 dest);
    
    void onExit();
    
private:
    PlayerType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    float _speed;
    FSM* _fsm;
    Progress* _progress;
    bool _isShowBar;
};

#endif