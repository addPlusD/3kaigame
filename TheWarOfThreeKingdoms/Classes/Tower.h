//
//  Tower.h
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 19/4/17.
//
//

#ifndef Tower_h
#define Tower_h

#include <stdio.h>
#include "cocos2d.h"
#include "Character.h"
#include "GameMaster.h"


class Tower : public cocos2d::Sprite{
public:
    static Tower* createTower(const std::string&, int);
    virtual bool init();
    void setHP(int);
    int getHP();
    void beDamaged(int);
    void takeDamage(Character*);
    bool findMinionArrived(Character*);
    void setBoundingBox();
private:
    int hp;
    cocos2d::Rect castleBoundingBox;
};



#endif /* Tower_hpp */
