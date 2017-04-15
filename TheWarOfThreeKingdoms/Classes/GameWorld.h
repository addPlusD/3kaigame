//
//  GameWorld.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#ifndef GAMEWORLD
#define GAMEWORLD

#include <stdio.h>
#include "cocos2d.h"
#include "Card.h"
#include "Character.h"
#include "GameMaster.h"

class GameWorld : public cocos2d::Layer{
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float);
    void setCards();
    void setBackground();
	void setMaster();
    

    CREATE_FUNC(GameWorld);


private:
	GameMaster* gameMaster;
};




#endif /* GameWorld_hpp */
