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

class Character : public cocos2d::Object{
    
public:
    virtual bool init();
    virtual void update();
    
    bool findEnemyWithinRange();
    //void move();
    void stopAndAttack();
    void loseBlood(int);
    void createCharacterOnPath();
    
    
private:
    int x, y;
    int health;
    int attackDamage;
    //int direction;
    float speed;
    bool attacking;
    
};

#endif /* Character_AbstractClass */
