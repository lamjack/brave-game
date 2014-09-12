//
//  FSM.h
//  Brave
//
//  Created by jack on 9/12/14.
//
//

#ifndef __Brave__FSM__
#define __Brave__FSM__

#include "cocos2d.h"

// Finite-state machine 狀態機
class FSM : public cocos2d::Ref{
public:
    bool init();
    
    static FSM* create(std::string state, std::function<void()> onEnter = nullptr);
    
    FSM(std::string state, std::function<void()> onEnter = nullptr);
    
    FSM* addState(std::string state, std::function<void()> onEnter = nullptr);
    
    FSM* addEvent(std::string eventName, std::string from, std::string to);

	bool isContainState(std::string stateName);

	void printState();

	void doEvent(std::string eventName);

	bool canDoEvent(std::string eventName);

	void setOnEnter(std::string state, std::function<void()> onEnter);
    
	std::string getState(){return _currentState;}
private:
    void changeToState(std::string state);
private:
    std::set<std::string> _states;
    
	std::unordered_map<std::string,std::unordered_map<std::string,std::string>> _events;
    
	std::unordered_map<std::string,std::function<void()>> _onEnters;
    
	std::string _currentState;
    
	std::string _previousState;
};

#endif /* defined(__Brave__FSM__) */
