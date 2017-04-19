//
//  Bar.hpp
//  TheWarOfThreeKingdoms
//
//  Created by keungkamtso on 18/4/2017.
//
//

#ifndef Bar_hpp
#define Bar_hpp

#include <stdio.h>
#include "cocos2d.h"

class Bar : public cocos2d::Sprite
{
public:
    Bar();
    ~Bar();
    
    static Bar* create(int);
    void setMaxHP(int);
    int getMaxHP();
    void updateHP(int);
    cocos2d::Rect getHPRect(int);

private:
    int maxHP;
};

#endif /* Bar_hpp */
