//
//  MainMenuScene.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 20/4/2017.
//
//

#ifndef MainMenuScene_h
#define MainMenuScene_h


#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    
    cocos2d::Sprite *mySprite;
    
    void Play(Ref *pSender);
    void Quit(Ref *pSender);
    
};


#endif /* MainMenuScene_hpp */
