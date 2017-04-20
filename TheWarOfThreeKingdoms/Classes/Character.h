//
//  Character.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#ifndef Character_AbstractClass
#define Character_AbstractClass


#include <stdio.h>
#include "cocos2d.h"
#include "Bar.h"
#include <string>

class Character : public cocos2d::Sprite {
    
public:
    virtual bool init();
    virtual void update(float delta);
    
    bool findEnemyWithinRange(Sprite* enemy);
    //void move();
    void stopAndAttack(Sprite* enemy);
    void loseBlood(int);
    void createCharacterOnPath();

	static Character* createCharacter(const std::string& _file, int direction);
	void createWalkAnimation(int);
	void setProperty(int health, int attackDamage, int attackRange,float speed, float);
	void die();

	//accessor method of the attributes
	float getSpeed();
    void setHealth(int);
	int getHealth();
    int getAttackDamage();
    
    float getPassedActionDuration();
    void setPassedActionDuration(float);
    
    void startPathing();
    void stopPathing();
    //void setMoveAction(cocos2d::MoveTo*);
    //cocos2d::MoveTo* getMoveAction();
	
    //void setCallbackAction(cocos2d::CallFuncN*);
    //cocos2d::CallFuncN* getCallbackAction();
    
    //for character's die callback
    void diedObject(cocos2d::Node*);
    
    //get the attack range bounding box
    cocos2d::Rect getAttackBoundingBox();

	//done hit sprite fading call back
	//void doneFading(cocos2d::Node*);
    
    //check attacking status
    bool getAttacking();
    void notAttackingNow();
    
    bool isStopped();
    void setStopped(bool);
    
    void setBoundingBox();
    
    void setSide(const std::string&);
    const std::string& getSide();
    
    void setLane(int);
    int getLane();
    
    bool getIsCooldown();
    
    void setActionSequence(cocos2d::Sequence*);
    cocos2d::Sequence* getActionSequence();

private:
    int x, y;
    int health;
    int attackDamage;
	int attackRange;
    int direction; //-1 = NPC  1=player
    float cooldown;
    float currentCooldown;
    float speed;
    float passedActionDuration;
    bool attacking;
    bool isCooldown;
    bool isPathing;
    bool stopped;
    int lane;
    std::string side;
	cocos2d::Vector<cocos2d::SpriteFrame *> walkAnimation;
	const char* fileName;
    cocos2d::MoveTo* moveTo;
    cocos2d::CallFuncN* callback;
    cocos2d::Sequence* actionSequence;
};

#endif /* Character_AbstractClass */
