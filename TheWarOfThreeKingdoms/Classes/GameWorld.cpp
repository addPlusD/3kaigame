//
//  GameWorld.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

//Implementing createScene member function of class GameWorld
Scene* GameWorld::createScene(){
    auto scene = Scene::create();
    
    auto layer = GameWorld::create();
    
    scene->addChild(layer);
    
    return scene;
}

//Implementing init member function of class GameWorld
bool GameWorld::init(){
    //do the init job here
    
    if (!Layer::init())
    {
        return false;
    }
    
    setBackground();
    setCards();
    
    //tell program to do update
    scheduleUpdate();
    
    return true;
}

//Implementing update member function of class GameWorld
void GameWorld::update(float delta){
    //do the update job here
    
    CCLOG("Updating...%f", delta);
}

void GameWorld::setCards() {
    
    auto card1 = Card::create("character1.png",9999,0);
    this->addChild(card1, 1);
    
    auto card2 = Card::create("character2.png", 998, 1);
    this->addChild(card2, 1);
    
    auto card3 = Card::create("arrow.png", 2, 2);
    this->addChild(card3, 1);
    
    auto card4 = Card::create("horse.png", 23, 3);
    this->addChild(card4, 1);
    
    auto card5 = Card::create("soldier.png", 242, 4);
    this->addChild(card5, 1);
    
}

void GameWorld::setBackground(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto tileMap = TMXTiledMap::create("AIGame_map.tmx");
    //    auto background = tileMap->layerNamed("Background");
    this->addChild(tileMap);
    
    auto tower01 = Sprite::create("tower.png");
    tower01->setTextureRect(Rect(26, 172, 50, 130));
    tower01->setPosition(Vec2(origin.x + tower01->getContentSize().width/2 ,
                              origin.y + tower01->getContentSize().height/2));
    this->addChild(tower01,1);
    
    auto tower02 = Sprite::create("tower.png");
    tower02->setTextureRect(Rect(26, 172, 50, 130));
    tower02->setPosition(Vec2(origin.x + visibleSize.width/2 - tower01->getContentSize().width/2 ,
                              origin.y + tower01->getContentSize().height/2));
    this->addChild(tower02,1);
    
    auto tower03 = Sprite::create("tower.png");
    tower03->setTextureRect(Rect(26, 172, 50, 130));
    tower03->setPosition(Vec2(origin.x + visibleSize.width - tower01->getContentSize().width/2 ,
                              origin.y + tower01->getContentSize().height/2));
    this->addChild(tower03,1);
    
    auto enemyTower01 = Sprite::create("tower.png");
    enemyTower01->setTextureRect(Rect(26, 172, 50, 130));
    enemyTower01->setPosition(Vec2(origin.x + enemyTower01->getContentSize().width/2 ,
                                   origin.y + visibleSize.height - enemyTower01->getContentSize().height/2));
    this->addChild(enemyTower01,1);
    
    auto enemyTower02 = Sprite::create("tower.png");
    enemyTower02->setTextureRect(Rect(26, 172, 50, 130));
    enemyTower02->setPosition(Vec2(origin.x + visibleSize.width/2 - enemyTower01->getContentSize().width/2 ,
                                   origin.y + visibleSize.height - enemyTower01->getContentSize().height/2));
    this->addChild(enemyTower02,1);
    
    auto enemyTower03 = Sprite::create("tower.png");
    enemyTower03->setTextureRect(Rect(26, 172, 50, 130));
    enemyTower03->setPosition(Vec2(origin.x + visibleSize.width - enemyTower01->getContentSize().width/2 ,
                                   origin.y + visibleSize.height - enemyTower01->getContentSize().height/2));
    this->addChild(enemyTower03,1);
}
