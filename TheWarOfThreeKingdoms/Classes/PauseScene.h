//
//  PauseScene.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 20/4/2017.
//
//

#ifndef PauseScene_hpp
#define PauseScene_hpp

#include <stdio.h>

class PauseScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);
    
    cocos2d::Sprite *mySprite;
    
    void Resume(Ref *pSender);
    void MainMenu(Ref *pSender);
    
};


#endif /* PauseScene_hpp */
