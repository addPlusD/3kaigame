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
#include <string>

class Character : public cocos2d::Sprite {
    
public:
    virtual bool init();
    virtual void update();
    
    bool findEnemyWithinRange();
    //void move();
    void stopAndAttack();
    void loseBlood(int);
    void createCharacterOnPath();

	static Character* createCharacter(const std::string& _file);
	void createWalkAnimation();

private:
    int x, y;
    int health;
    int attackDamage;
    //int direction;
    float speed;
    bool attacking;
	cocos2d::Vector<cocos2d::SpriteFrame *> walkAnimation;
	const char* fileName;
    
};

#endif /* Character_AbstractClass */
