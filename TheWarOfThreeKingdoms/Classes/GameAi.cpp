//
//  GameAi.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 18/4/2017.
//
//

#include "GameAi.h"
#include <stdlib.h>     /* srand, rand */

USING_NS_CC;
using namespace ui;

static GameAi* gameAi = nullptr;
GameAi* GameAi::getInstance() {
    gameAi = new GameAi();
    return gameAi;
}


GameAi::GameAi() {
}

GameAi::~GameAi() {
}

void GameAi::init(int lv){
   //top
    for (int i=0; i<lv; i++) {
        createSoldier(soliderSet1[i], 1, 650,-1);
    }
    //mid
    for (int i=0; i<lv; i++) {
        createSoldier(soliderSet2[i], 1, 450,0);
    }
    //bot
    for (int i=0; i<lv; i++) {
        createSoldier(soliderSet3[i], 1, 250,1);
    }
}


void GameAi::update(){

    GameMaster *gM = GameMaster::getInstance();
    //strategy 1 if high power(hp) character exist, sd defence team(archer1);
    //strategy 2 if high power(dmg) character exist, sd defence team(archer2);
    //strategy 3 if away character is too close(x:100 is the tower x:500 is the mid), sd defence team(knight);
    
    //strategy 4 random raider team (if away character close to tower, higher chance to hv raider)
    
    //if s1 and s3 doesnot hv a high chance, sd defence team(solider)
    
    int maxHpOnLane =0, highestPowerCharacter = 0, closetPosition = -1;
    int strategy1 =0, strategy2 =0, strategy3 =0;
    //check the position , hp and dmg for each lane
    
    for (int i = 0; i<3; i++) {
        for (Character* character : gM->getAwayCharacter(i)) {
            if (character->getHealth()>maxHpOnLane) {
                maxHpOnLane=character->getHealth();
                strategy1=i-1;
            }
            if (character->getAttackDamage()>highestPowerCharacter) {
                highestPowerCharacter=character->getAttackDamage();
                strategy2=i-1;
            }
            if (character->getPositionX()>closetPosition) {
                closetPosition=character->getPositionX();
                strategy3=i-1;
            }
        }
    }
    
    //s3>s2>s1
    float strat1 = maxHpOnLane/500;
    float strat2 = highestPowerCharacter/50;
    
    if(closetPosition<300&&closetPosition!=-1){
        //too close, sd defence team(knight) to that lane
        for (int i=0; i<2; i++) {
            createSoldier(defenceTeam1[i], 1, findlanePosition(strategy3),strategy3);
             CCLOG("createSoldier 1");
        }
    }else if (strat2>0.5){
        //high power(dmg), sd defence team(archer1) to that lane
        for (int i=0; i<2; i++) {
            createSoldier(defenceTeam2[i], 1, findlanePosition(strategy2),strategy2);
            CCLOG("createSoldier 2");
        }
    }else if (strat1>0.5){
        //high power(hp), sd defence team(archer2) to that lane
        for (int i=0; i<2; i++) {
            createSoldier(defenceTeam3[i], 1, findlanePosition(strategy1),strategy1);
                 CCLOG("createSoldier 3");
        }
    }else{
        int random = rand()%3-1;
        createSoldier(rand()%3, 1, findlanePosition(random),random);
        CCLOG("createSoldier 4");
    }
    
    
}

int GameAi::findlanePosition(int i){
    
    switch (i) {
        case -1:
            return 650;
            break;
        case 0:
            return 450;
            break;
        case 1:
            return 250;
            break;
    }
    return 0;
}

void GameAi::createSoldier(int sol, int quantity, int position,int lane){

    // soldier 0, archer 1, knight 2
    for (int i=0; i<quantity; i++) {
        string fileName[3] = { "moveCharacter10.png", "moveCharacter9.png","moveCharacter8.png"};
        auto newCharacter = Character::createCharacter(fileName[sol].c_str(), 2);
        switch (sol) {
            case 0:
                // int health, int attackDamage, int attackRange, float speed, float cooldown
                newCharacter->setProperty(50, 10, 10, 12, 3);
                newCharacter->setName("soldier");
                break;
                
            case 1:
                newCharacter->setProperty(30, 5, 60, 15, 3);
                newCharacter->setName("archer");
                break;
                
            case 2:
                newCharacter->setProperty(60, 12, 20, 8, 2);
                newCharacter->setName("knight");
                break;
        }
        
        auto scene = cocos2d::Director::getInstance()->getRunningScene()->getChildByTag(999);
        scene->addChild(newCharacter, 1);
        newCharacter->setPosition(Vec2(100, position));
        GameMaster::getInstance()->createAiAction(newCharacter);
        GameMaster::getInstance()->addCharacterToLane(lane, newCharacter , "home");
    }
}




