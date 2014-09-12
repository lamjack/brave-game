//
//  MainScene.cpp
//  Brave
//
//  Created by jack on 9/11/14.
//
//

#include "MainScene.h"
#include "Player.h"

USING_NS_CC;

Scene* MainScene::createScene(){
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init(){
    if(!Layer::init()){
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist", "image/role.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist", "image/ui.pvr.ccz");
    
    Sprite* background = Sprite::create("image/background.png");
    background->setPosition(origin + visibleSize/2);
    this->addChild(background);
   
    _player = Player::create(Player::PlayerType::PLAYER);
    _player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height/2);
    this->addChild(_player);
    
    _enemy1 = Player::create(Player::PlayerType::ENEMY1);
    _enemy1->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height/2);
    this->addChild(_enemy1);
    
    _enemy1->playAnimationForever(1);
    
    _listenerTouch = EventListenerTouchOneByOne::create();
    _listenerTouch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);
    
    _progress = Progress::create("player-progress-bg.png","player-progress-fill.png");
    _progress->setPosition(VisibleRect::left().x + _progress->getContentSize().width / 2, VisibleRect::top().y - _progress->getContentSize().height / 2);
    this->addChild(_progress);
    
    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event){
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    _player->walkTo(pos);
    return true;
}

