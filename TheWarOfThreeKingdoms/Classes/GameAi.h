//
//  GameAi.hpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 18/4/2017.
//
//

#ifndef GameAi_hpp
#define GameAi_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.h"
#include "CharacterCreator.h"
#include "GameMaster.h"
#include "ui/CocosGUI.h"

class GameAi{
public:
    static GameAi* getInstance();
    GameAi();
    ~GameAi();
    void init(int);
    void update();
private:
	int lv;
    int findlanePosition(int );
    void createSoldier(int,int,int,int);
    int soliderSet1[3]={0,1,0};
    int soliderSet2[3]={1,0,2};
    int soliderSet3[3]={2,1,2};
    int defenceTeam1[2]={2,2};//(knight team)
    int defenceTeam2[2]={0,1};//(archer team1)
    int defenceTeam3[2]={1,1};//(archer team2)
    int raiderTeam[5]={2,2,2,1,1};
};
#endif /* GameAi_hpp */
