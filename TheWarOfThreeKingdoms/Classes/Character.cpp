//
//  Character.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "Character.h"
USING_NS_CC;

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

Character* Character::createCharacter(const std::string& _file)
{
	Character* pCharacter = new Character();

	if (pCharacter->initWithFile(_file.c_str(), Rect(0, 32, 32, 32))) {
		pCharacter->fileName = _file.c_str();
		pCharacter->setPosition(Vec2(300, 300));
		pCharacter->setScale(3);
		pCharacter->createWalkAnimation();

		return pCharacter;
	}

	CC_SAFE_DELETE(pCharacter);
	return NULL;

}

void Character::createWalkAnimation()
{
	this->walkAnimation.reserve(3);
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(0, 32, 32, 32)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(32, 32, 32, 32)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(64, 32, 32, 32)));

	Animation* animation = Animation::createWithSpriteFrames(this->walkAnimation, 0.2f);
	Animate* animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

