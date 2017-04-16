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
#include <stdlib.h> 

class Character : public cocos2d::Sprite {
    
public:
    virtual bool init();
    virtual void update(float delta);
    
    void findEnemyWithinRange(Sprite* enemy);
    //void move();
    void stopAndAttack(Sprite* enemy);
    void loseBlood(int);
    void createCharacterOnPath();

	static Character* createCharacter(const std::string& _file, int direction);
	void createWalkAnimation();
	void setProperty(int health, int attackDamage, int attackRange,float speed);

private:
    int x, y;
    int health;
    int attackDamage;
	int attackRange;
    int direction; //-1 = NPC  1=player
    float speed;
    bool attacking;
	cocos2d::Vector<cocos2d::SpriteFrame *> walkAnimation;
	const char* fileName;
    
};

#endif /* Character_AbstractClass */
