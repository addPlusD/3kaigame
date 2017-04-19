//
//  Tower.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 19/4/17.
//
//

#include "Tower.h"

USING_NS_CC;

Tower* Tower::createTower(const std::string& _file, int hp)
{
    Tower* pTower = new Tower();
    //Eddie on 20170419
    if(pTower && pTower->init()){
        if (pTower->initWithFile(_file.c_str()) ){
            pTower->autorelease();
            pTower->setHP(hp);
            return pTower;
        }
    }
    
    CC_SAFE_DELETE(pTower);
    return NULL;
    
}

bool Tower::init(){
    return true;
}

void Tower::setHP(int hp){
    this->hp = hp;
}

int Tower::getHP(){
    return this->hp;
}

void Tower::beDamaged(int hp){
    this->hp-=hp;
}

void Tower::setBoundingBox(){
    auto originalBoundingBox = this->getBoundingBox();
    if(this->getName()=="awayTower"){
        castleBoundingBox = originalBoundingBox;
    } else {
        castleBoundingBox = originalBoundingBox;
    }
}

bool Tower::findMinionArrived(Character* character){
    if(this->castleBoundingBox.intersectsRect(character->getAttackBoundingBox())){
        CCLOG("Tower is going to be damaged!!");
        CCLOG("HP left: %d", this->hp);
        return true;
    }
    return false;
}

void Tower::takeDamage(Character* character){
    if(character->getIsCooldown()){
        CCLOG("Tower got %d damaged", character->getAttackDamage());
		CCLOG("HP left: %d", this->hp);
        this->beDamaged(character->getAttackDamage());
    } else {
        CCLOG("Luckily player is cooling down");
    }
}


