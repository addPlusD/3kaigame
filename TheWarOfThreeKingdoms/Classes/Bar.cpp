//
//  Bar.cpp
//  TheWarOfThreeKingdoms
//
//  Created by keungkamtso on 18/4/2017.
//
//

#include "Bar.h"
USING_NS_CC;

Bar::Bar(){
    
}

Bar::~Bar()
{
}

Bar* Bar::create(int maxHP)
{
    Bar* pBar = new Bar();
    pBar = (Bar*) Sprite::create("HP_bar.png");
    pBar->setTextureRect(Rect(0, 0, 312, 52));
    pBar->setMaxHP(maxHP);
    
    return pBar;
}

void Bar::setMaxHP(int hp){
    this->maxHP=hp;
}

int Bar::getMaxHP(){
    return this->maxHP;
}

void Bar::updateHP(int hp){
    hp = (int)(hp*25/this->maxHP);
    setTextureRect(getHPRect(hp));
}

Rect Bar::getHPRect(int hp){
    switch (hp){
        case 25:
            return Rect(0, 0, 312, 52);
            break;
        case 24:
            return Rect(624, 0, 312, 52);
            break;
        case 23:
            return Rect(312, 52, 312, 52);
            break;
        case 22:
            return Rect(0, 104, 312, 52);
            break;
        case 21:
            return Rect(624, 104, 312, 52);
            break;
        case 20:
            return Rect(312, 156, 312, 52);
            break;
        case 19:
            return Rect(0, 208, 312, 52);
            break;
        case 18:
            return Rect(624, 208, 312, 52);
            break;
        case 17:
            return Rect(312, 260, 312, 52);
            break;
        case 16:
            return Rect(0, 312, 312, 52);
            break;
        case 15:
            return Rect(624, 312, 312, 52);
            break;
        case 14:
            return Rect(312, 364, 312, 52);
            break;
        case 13:
            return Rect(0, 416, 312, 52);
            break;
        case 12:
            return Rect(624, 416, 312, 52);
            break;
        case 11:
            return Rect(312, 468, 312, 52);
            break;
        case 10:
            return Rect(0, 520, 312, 52);
            break;
        case 9:
            return Rect(624, 520, 312, 52);
            break;
        case 8:
            return Rect(312, 572, 312, 52);
            break;
        case 7:
            return Rect(0, 624, 312, 52);
            break;
        case 6:
            return Rect(624, 624, 312, 52);
            break;
        case 5:
            return Rect(312, 676, 312, 52);
            break;
        case 4:
            return Rect(0, 728, 312, 52);
            break;
        case 3:
            return Rect(624, 780, 312, 52);
            break;
        case 2:
            return Rect(312, 780, 312, 52);
            break;
        case 1:
            return Rect(0, 832, 312, 52);
            break;
        case 0:
            return Rect(312, 832, 312, 52);
            break;
        default:
            return Rect(312, 832, 312, 52);
            break;
    }
}
