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
USING_NS_CC;

class Player : public Sprite{

public:
	enum PlayerType
	{
		PLAYER,
		ENEMY1,
		ENEMY2
	};
    
	bool initWithPlayerType(PlayerType type);
	static Player* create(PlayerType type);
    void addAnimation();
    
private:
    PlayerType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
};

#endif