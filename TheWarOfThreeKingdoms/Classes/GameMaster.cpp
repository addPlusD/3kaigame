//
//  GameMaster.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameMaster.h"

USING_NS_CC;


GameMaster* GameMaster::createMaster(){
    
}


bool GameMaster::init(){
    if(!Layer::init()){
        return false;
    }
    
    return true;
}

void GameMaster::addSquadToLane(int laneInd, Squad* squad){
    Vector<Squad*> lane = getHomeLaneVector(laneInd);
    //lane.pushBack(squad);
}

void GameMaster::removeSquadFromLane(int laneInd, Squad* squad){
    Vector<Squad*> lane = getHomeLaneVector(laneInd);
    //lane.erase(lane.find(squad));
}

void GameMaster::addCharacterToLane(int laneInd, Character* character){
    Vector<Character*> lane = getAwayLaneVector(laneInd);
    //lane.pushBack(character);
}

void GameMaster::removeCharacterFromLane(int laneInd, Character* character){
    Vector<Character*> lane = getAwayLaneVector(laneInd);
    //lane.erase(lane.find(squad));
}

Vector<Squad*> GameMaster::getHomeLaneVector(int laneIndicator){
    Vector<Squad*> target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = HOME_TOP;
            break;
        case 0:
            target = HOME_MID;
            break;
        case 1:
            target = HOME_BOT;
            break;
    }
    return target;
}

Vector<Character*> GameMaster::getAwayLaneVector(int laneIndicator){
    Vector<Character*> target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = AWAY_TOP;
            break;
        case 0:
            target = AWAY_MID;
            break;
        case 1:
            target = AWAY_BOT;
            break;
    }
    return target;
}

void GameMaster::checkCollision(){
    
}