//
//  GameWorld.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameWorld.h"


USING_NS_CC;


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
