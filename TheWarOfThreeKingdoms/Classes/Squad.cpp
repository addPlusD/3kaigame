//
//  Squard.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "Squad.h"

USING_NS_CC;


bool Squad::init(){
    this->attacking = false;
    return true;
}

void Squad::update(){
    if(!attacking){
        //do move here
    }
    //find if there is enemy after move
    //if it is stop and attack, then update the attacking tag
}

bool Squad::findEnemyWithinRange(){
    return true;
}

void Squad::stopAndAttack(){
    
}

void Squad::loseBlood(int damage){
    this->health -= damage;
}

void Squad::createCharacterOnPath(){
    
}