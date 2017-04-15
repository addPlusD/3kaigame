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
    return GameMaster::create();
}


bool GameMaster::init(){
    if(!Layer::init()){
        return false;
    }

	EventListenerMouse* switchLaneListener = EventListenerMouse::create();
	switchLaneListener->onMouseDown = CC_CALLBACK_1(GameMaster::switchLaneCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(switchLaneListener, this);
	
    
    return true;
}


void GameMaster::switchLaneCallback(Event* e) {
	EventMouse* mouseEvent = (EventMouse*)e;
	//get the layer, then get the click position, check if it is in the lane layer
	//if yes, then check its laneNumber and change the value of currentLane respectively
	auto scene = CCDirector::getInstance()->getRunningScene();
	auto mainWorld = scene->getChildByTag(999);
	TMXTiledMap* map = (TMXTiledMap*) mainWorld->getChildByName("GameMap");
	TMXLayer* laneLayer = map->getLayer("lane");
	//get the cocos2d cursor position
	Vec2 cursorCocosPosition = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	//get the cursor position for the tile coordinate (y is inverse to the cocos2d coordinate system)
	Vec2 cursorTilePosition = Vec2((cursorCocosPosition.x)/laneLayer->getMapTileSize().width, (CCDirector::getInstance()->getWinSize().height - cursorCocosPosition.y)/laneLayer->getMapTileSize().height);
	CCLOG("Cocos2d: (x,y)=(%f,%f)", cursorCocosPosition.x, cursorCocosPosition.y);
	CCLOG("Tile: (x,y)=(%f,%f)", cursorTilePosition.x, cursorTilePosition.y);
	//use the tile cursor position to check if there is a tile in the laneLayer, if it is check the laneNumber value and switch the lane
	int targetGID = laneLayer->getTileGIDAt(cursorTilePosition);
	//check for the gid, 18=top, 22=mid, 26=bot
	//if hit anyone of them, change the currentLane
	//otherwise remain unchanged(remain the last currentLane value)
	if (targetGID !=0) {
		CCLOG("GID not = 0: %d", targetGID);
		switch (targetGID){
		case 0: return;
		case 18: 
			currentLane = top;
			CCLOG("Lane switched to top");
			break;
		case 22:
			currentLane = mid;
			CCLOG("Lane switched to mid");
			break;
		case 26:
			currentLane = bot;
			CCLOG("Lane switched to bot");
			break;
		default:
			CCLOG("Cannot detect valid GID");
			break;
		}
	}

	CCLOG("The updated lane selector: %d", (int)currentLane);


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
