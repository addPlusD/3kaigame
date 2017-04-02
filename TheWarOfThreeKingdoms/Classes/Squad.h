//
//  Squard.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#ifndef Squard_AbstractClass
#define Squard_AbstractClass

#include <stdio.h>
#include "cocos2d.h"

class Squad : public cocos2d::Object{

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



#endif /* Squard_AbstractClass */
