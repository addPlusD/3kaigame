//
//  GameMaster.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#ifndef GameMaster_class
#define GameMaster_class

#include <stdio.h>
#include "cocos2d.h"
#include "Squad.h"
#include "Character.h"

class GameMaster : public cocos2d::Layer{
    
	enum _currentLane { top = -1, mid = 0, bot = 1 };

public:
    static GameMaster* createMaster();
    virtual bool init();
    //add and remove squad from lane
    //@param 1)lane vector 2)squad object
    void addSquadToLane(int , Squad*);
    void removeSquadFromLane(int, Squad*);
    
    //add and remove character from lane
    //@param 1)lane vector 2)character object
    void addCharacterToLane(int, Character*);
    void removeCharacterFromLane(int, Character*);
    
    cocos2d::Vector<Squad*> getHomeLaneVector(int);
    cocos2d::Vector<Character*> getAwayLaneVector(int);
    
	void switchLaneCallback(cocos2d::Event*);

    void checkCollision();
    
    CREATE_FUNC(GameMaster);
    
private:
    cocos2d::Vector<Squad*> HOME_TOP, HOME_MID, HOME_BOT;
    cocos2d::Vector<Character*> AWAY_TOP, AWAY_MID, AWAY_BOT;
	_currentLane currentLane;
};

#endif /* GameMaster_class */
