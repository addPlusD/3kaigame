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
    
    
    //tell program to do update
    scheduleUpdate();
    
    return true;
}

//Implementing update member function of class GameWorld
void GameWorld::update(float delta){
    //do the update job here
    
    CCLOG("Updating...%f", delta);
}