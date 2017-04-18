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
#include "Bar.h"

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
    
    std::vector<Squad*>* getHomeSquadLaneVector(int);
	std::vector<Squad*>* getAwaySquadLaneVector(int);
    std::vector<Character*>* getAwayCharacterLaneVector(int);
	std::vector<Character*>* getHomeCharacterLaneVector(int);
    
	void switchLaneCallback(cocos2d::Event*);
	void clickOnCard(int, int);

    void checkCollision();
	void update(float delta);
    
    void createAction(Character*);
    void resumeAction(Character*);
    
    
	
    CREATE_FUNC(GameMaster);
    
private:

		std::vector<Squad*> HOME_TOP_SQUAD;
		std::vector<Squad*> HOME_MID_SQUAD;
		std::vector<Squad*> HOME_BOT_SQUAD;
		std::vector<Squad*> AWAY_TOP_SQUAD;
		std::vector<Squad*> AWAY_MID_SQUAD;
		std::vector<Squad*> AWAY_BOT_SQUAD;
		std::vector<Character*> HOME_TOP_CHARACTER;
		std::vector<Character*> HOME_MID_CHARACTER;
		std::vector<Character*> HOME_BOT_CHARACTER;
		std::vector<Character*> AWAY_TOP_CHARACTER;
		std::vector<Character*> AWAY_MID_CHARACTER;
		std::vector<Character*> AWAY_BOT_CHARACTER;

	cocos2d::Sprite* arrowIndicatorSprite;

	
	int currentLane;
	
	float timeStamp=0;
	bool cardCoolDown = false;
};

#endif /* GameMaster_class */
