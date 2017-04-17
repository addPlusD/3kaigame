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
#include "CharacterCreator.h"

class GameMaster : public cocos2d::Layer{
    

#ifndef _PositionInfo
#define _PositionInfo
#define awaySpawnPositionX 900.0
#define topLaneY 650.0
#define midLaneY 450.0
#define botLaneY 250.0
#define homeSpawnPositionX 100.0
#endif

#ifndef _laneInfo
#define _laneInfo
#define laneTop -1
#define laneMid 0
#define laneBot 1
#endif


public:
	static GameMaster* getInstance();

    virtual bool init();
	GameMaster();
	~GameMaster();
    //add and remove squad from lane
    //@param 1)lane vector 2)squad object 3)side(home or away)
    void addSquadToLane(int , Squad*, const std::string&);
    void removeSquadFromLane(int, Squad*, const std::string&);
    
    //add and remove character from lane
    //@param 1)lane vector 2)character object
    void addCharacterToLane(int, Character*, const std::string&);
    void removeCharacterFromLane(int, Character*, const std::string&);
    
    cocos2d::Vector<Squad*>* getHomeSquadLaneVector(int);
	cocos2d::Vector<Squad*>* getAwaySquadLaneVector(int);
    cocos2d::Vector<Character*>* getAwayCharacterLaneVector(int);
	cocos2d::Vector<Character*>* getHomeCharacterLaneVector(int);
    
	void switchLaneCallback(cocos2d::Event*);
	void clickOnCard(int, int);

    void checkCollision();
	void update(float delta);
	
    CREATE_FUNC(GameMaster);
    
private:

		cocos2d::Vector<Squad*> HOME_TOP_SQUAD;
		cocos2d::Vector<Squad*> HOME_MID_SQUAD;
		cocos2d::Vector<Squad*> HOME_BOT_SQUAD;
		cocos2d::Vector<Squad*> AWAY_TOP_SQUAD;
		cocos2d::Vector<Squad*> AWAY_MID_SQUAD;
		cocos2d::Vector<Squad*> AWAY_BOT_SQUAD;
		cocos2d::Vector<Character*> HOME_TOP_CHARACTER;
		cocos2d::Vector<Character*> HOME_MID_CHARACTER;
		cocos2d::Vector<Character*> HOME_BOT_CHARACTER;
		cocos2d::Vector<Character*> AWAY_TOP_CHARACTER;
		cocos2d::Vector<Character*> AWAY_MID_CHARACTER;
		cocos2d::Vector<Character*> AWAY_BOT_CHARACTER;

	cocos2d::Sprite* arrowIndicatorSprite;

	
	int currentLane;

};

#endif /* GameMaster_class */
