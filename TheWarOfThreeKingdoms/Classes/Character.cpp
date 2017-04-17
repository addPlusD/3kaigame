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

void Character::update(float delta){
	this->attacking = false;
	//this->findEnemyWithinRange(Sprite* enemy); loop through all element in vector
    //if(!attacking){
	//  continue run action
    //}
}

void Character::findEnemyWithinRange(Sprite* enemy){
	if (abs(this->getPositionX() - enemy->getPositionX()) < this->attackRange) {
		this->attacking = true;
		this->stopAndAttack(static_cast<Character*>(enemy));
		CCLOG("find enemy within %d ",this->attackRange);
	}

}

void Character::stopAndAttack(Sprite* enemy) {
	//this->stopAllActions(); //stop the running action
	this->stopAction(this->moveTo);
	static_cast<Character*>(enemy)->loseBlood(this->attackDamage);
}

void Character::loseBlood(int damage){
    this->health -= damage;
	CCLOG("Enemy health: %d",this->health);
}

void Character::die() {
	auto fadeOut = FadeOut::create(1.0f);
	this->runAction(fadeOut);
}

void Character::createCharacterOnPath(){
    
}

Character* Character::createCharacter(const std::string& _file, int direction)
{
	Character* pCharacter = new Character();

	if (pCharacter->initWithFile(_file.c_str(), Rect(0, direction*39, 32, 38))) {
		pCharacter->autorelease();
		pCharacter->fileName = _file.c_str();
		pCharacter->setPosition(Vec2(800, 300));
		pCharacter->setScale(2);
		//pCharacter->setScaleX(direction);
		pCharacter->createWalkAnimation();
		return pCharacter;
	}

	CC_SAFE_DELETE(pCharacter);
	return NULL;

}

void Character::createWalkAnimation()
{
	this->walkAnimation.reserve(3);
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(0, 39, 32, 38)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(32, 39, 32, 38)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(64, 39, 32, 38)));

	Animation* animation = Animation::createWithSpriteFrames(this->walkAnimation, 0.2f);
	Animate* animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void Character::setProperty(int health, int attackDamage, int attackRange, float speed) {
	this->health = health;
	this->attackDamage = attackDamage;
	this->attackRange = attackRange;
	this->speed = speed;
}

float Character::getSpeed() {
	return this->speed;
}
