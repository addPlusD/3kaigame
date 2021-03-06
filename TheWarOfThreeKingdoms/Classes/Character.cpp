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
	//init the hit sprite for further use
	auto hitSprite = Sprite::create("hit.png");
	hitSprite->setName("hitSprite");
	hitSprite->setPosition(this->getPositionX(), this->getPositionY() + this->getContentSize().height+50);
	hitSprite->setScale(0.15);
	hitSprite->setVisible(false);
	this->addChild(hitSprite);
    currentCooldown = cooldown;
    this->attacking = false;
    this->isCooldown = true;
    this->actionSequence = nullptr;
    this->isPathing = false;
    this->stopped = false;
	this->side = "home";

    scheduleUpdate();
    return true;
}

Character* Character::createCharacter(const std::string& _file, int direction)
{
    //direction: 0=down, 1=left, 2=right, 3=up
    Character* pCharacter = new Character();
    //Eddie on 20170418
    if(pCharacter && pCharacter->init()){
        if (pCharacter->initWithFile(_file.c_str(), Rect(0, direction*39, 32, 38))) {
            pCharacter->autorelease();
            pCharacter->fileName = _file.c_str();
            pCharacter->setPosition(Vec2(800, 300));
            pCharacter->setScale(2);
            //pCharacter->setScaleX(direction);
            pCharacter->createWalkAnimation(direction);
            return pCharacter;
        }
    }
    
    
    CC_SAFE_DELETE(pCharacter);
    return nullptr;
    
}



void Character::setLane(int lane){
    this->lane = lane;
}

int Character::getLane(){
    return this->lane;
}

bool Character::getIsCooldown(){
    return isCooldown;
}

void Character::update(float delta){
	//this->findEnemyWithinRange(Sprite* enemy); loop through all element in vector
    //if(!attacking){
	//  continue run action
    //}
    if(this->isCooldown){
        //ready to attack
        this->currentCooldown = this->cooldown;
        this->isCooldown = true;
    } else {
        //cooling down
        //CCLOG("Cooling down!");
        this->currentCooldown -= delta;
        if(this->currentCooldown<=0){
            this->isCooldown = true;
            this->currentCooldown = this->cooldown;
        }
    }
    //update the duration timer, it stores how much time still needed to the destination
    if(isPathing){
        passedActionDuration-=delta;
    }
    }

void Character::startPathing(){
    isPathing = true;
}

void Character::stopPathing(){
    isPathing = false;
}

bool Character::findEnemyWithinRange(Sprite* enemy){
	//CCLOG("Actual range between %s and %s: %f",this->getName().c_str(), enemy->getName().c_str(),abs(this->getPositionX() - enemy->getPositionX()));
    //if (abs(this->getPositionX() - enemy->getPositionX()) < this->attackRange && !this->attacking && this->isCooldown) {
    
    auto myBoundingBox = this->getAttackBoundingBox();
    auto enemyBoundingBox = enemy->getBoundingBox();
    //CCLOG("myBoundingBox: %f, %f", myBoundingBox.origin.x, myBoundingBox.origin.y);
    //CCLOG("enemyBoundingBox: %f, %f", enemyBoundingBox.origin.x, enemyBoundingBox.origin.y);
    if(myBoundingBox.intersectsRect(enemyBoundingBox)){
        this->stopAction(this->actionSequence);
        //start attack, stop the action
        //action stopped flag -> tell the master to resume action
        this->stopped = true;
        this->stopPathing();
		this->attacking = true;
		this->stopAndAttack(static_cast<Character*>(enemy));
        CCLOG("Attacker %s founds enemy %s in range %d",this->getName().c_str(), enemy->getName().c_str(), this->attackRange);
        return true;
    }
    return false;

}

void Character::setSide(const std::string& s){
    this->side = s;
}

const std::string& Character::getSide(){
    return this->side;
}


bool Character::isStopped(){
    return this->stopped;
}

void Character::setStopped(bool b){
    this->stopped = b;
}

bool Character::getAttacking(){
    return this->attacking;
}

void Character::notAttackingNow(){
    this->attacking = false;
}

void Character::stopAndAttack(Sprite* enemy) {
	//this->stopAllActions(); //stop the running action
	//Director::getInstance()->getActionManager()->pauseTarget(this);
	//this->stopAction(this->moveTo);
	
    if(this->attacking && isCooldown){
		auto hitSprite = this->getChildByName("hitSprite");
		//make the sprite be visible now
		hitSprite->setVisible(true);
		//set the fade in and fade out to the hit sprite
		auto fadeIn = FadeIn::create(0.2f);
		auto fadeOut = FadeOut::create(0.2f);
		//auto fadeDoneCallback = CallFuncN::create(CC_CALLBACK_1(Character::doneFading, this));
		auto sequence = Sequence::create(fadeIn, fadeOut, nullptr);
		hitSprite->runAction(sequence);
		//cool down the character
        this->isCooldown = false;
		//damage the enemy
        static_cast<Character*>(enemy)->loseBlood(this->attackDamage);
		
    }
}

//void Character::doneFading(Node* sender) {
//	Sprite* theSender = (Sprite*)sender;
//	theSender->removeFromParent();
//}

void Character::loseBlood(int damage){
    this->health -= damage;
    auto HPBar= (Bar*)this->getChildByTag(101);
    HPBar->updateHP(this->health);
	CCLOG("Enemy health: %d",this->health);
	this->attacking = false;
}

void Character::die() {
	auto fadeOut = FadeOut::create(0.3f);
    auto dieCallback = CallFuncN::create(CC_CALLBACK_1(Character::diedObject, this));
    auto runSequence = Sequence::create(fadeOut, dieCallback, nullptr);
	this->runAction(runSequence);
	this->getChildByTag(101)->runAction(runSequence->clone());
}

void Character::diedObject(Node* sender){
    Sprite* sprite = (Sprite*) sender;
	sprite->removeAllChildren();
    sprite->removeFromParent();
}

void Character::setHealth(int hp){
    this->health = hp;
}

int Character::getHealth(){
    return this->health;
}

int Character::getAttackDamage(){
    return this->attackDamage;
}

void Character::createCharacterOnPath(){
    
}



void Character::createWalkAnimation(int direction)
{
	this->walkAnimation.reserve(3);
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(0, direction*39, 32, 38)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(32, direction*39, 32, 38)));
	this->walkAnimation.pushBack(SpriteFrame::create(this->fileName, Rect(64, direction*39, 32, 38)));

	Animation* animation = Animation::createWithSpriteFrames(this->walkAnimation, 0.2f);
	Animate* animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void Character::setProperty(int health, int attackDamage, int attackRange, float speed, float cooldown) {
	this->health = health;
	this->attackDamage = attackDamage;
	this->attackRange = attackRange;
	this->speed = speed;
    this->cooldown = cooldown;
    
    auto HPBar = Bar::create(health);
    HPBar->setScale(0.1);
    HPBar->setTag(101);
    HPBar->setPosition(Vec2(this->getContentSize().width/2,30));
    this->addChild(HPBar, 1);
    
    
    
}

Rect Character::getAttackBoundingBox(){
    
    
    auto originalBoundingBox = this->getBoundingBox();
    float increment = 0.3 * this->attackRange;
    float newOriginX = originalBoundingBox.origin.x-increment;
    float newOriginY = originalBoundingBox.origin.y;
    float newWidth = originalBoundingBox.getMaxX() - originalBoundingBox.getMinX() + increment;
    float newHeight = originalBoundingBox.getMaxY() - originalBoundingBox.getMinY();
    
    //CCLOG("OriginalBoundingBox: %f, %f", originalBoundingBox.origin.x, originalBoundingBox.origin.y);
    
	originalBoundingBox.setRect(newOriginX, newOriginY, newWidth, newHeight);
	

    
    return originalBoundingBox;
}

float Character::getSpeed() {
	return this->speed;
}

/*MoveTo* Character::getMoveAction(){
    return this->moveTo;
}

void Character::setMoveAction(MoveTo* moveAction){
    this->moveTo = moveAction;
}

CallFuncN* Character::getCallbackAction(){
    return this->callback;
}

void Character::setCallbackAction(CallFuncN* callbackAction){
    this->callback = callbackAction;
}*/

Sequence* Character::getActionSequence(){
    return this->actionSequence;
}

void Character::setActionSequence(Sequence* actionSequence){
    this->actionSequence = actionSequence;
}

float Character::getPassedActionDuration(){
    return this->passedActionDuration;
}

void Character::setPassedActionDuration(float s){
    this->passedActionDuration = s;
}
