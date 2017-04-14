//
//  Character.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "Character.h"

bool Character::init(){
    this->attacking = false;
    return true;
}

void Character::update(){
    if(!attacking){
        //do move here
    }
    //find if there is enemy after move
    //if it is stop and attack, then update the attacking tag
}

bool Character::findEnemyWithinRange(){
    return true;
}

void Character::stopAndAttack(){
    
}

void Character::loseBlood(int damage){
    this->health -= damage;
}

void Character::createCharacterOnPath(){
    
}
