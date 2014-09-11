#include "HelloWorldScene.h"
#include "Player.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* background = Sprite::create("image/background.png");
    background->setPosition(origin + visibleSize/2);
    this->addChild(background);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist", "image/role.pvr.ccz");
    
    Player* player = Player::create(Player::PlayerType::PLAYER);
    player->setPosition(origin.x + player->getContentSize().width/2, origin.y + visibleSize.height/2);
    this->addChild(player);
    
    Player* enemy1 = Player::create(Player::PlayerType::ENEMY1);
    enemy1->setPosition(origin.x + visibleSize.width - player->getContentSize().width/2, origin.y + visibleSize.height/2);
    this->addChild(enemy1);
    
    player->playAnimationForever(1);
    enemy1->playAnimationForever(1);
    
    return true;
}

