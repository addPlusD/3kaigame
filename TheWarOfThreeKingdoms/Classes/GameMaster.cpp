//
//  GameMaster.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameMaster.h"

USING_NS_CC;


static GameMaster* gameMaster = nullptr;
static bool isCreated = false;
int currentLane;

////GameMaster* GameMaster::createMaster(){
////    //return GameMaster::create();
////	gameMaster = GameMaster::create();
////	return gameMaster;
////}

GameMaster* GameMaster::getInstance() {
	if (!isCreated) {
		gameMaster = new GameMaster();
		if (gameMaster && gameMaster->init()) {
			gameMaster->autorelease();
			return gameMaster;
		}
		CC_SAFE_DELETE(gameMaster);
	}
	return gameMaster;
}


bool GameMaster::init(){
    if(!Layer::init()){
        return false;
    }

	EventListenerMouse* switchLaneListener = EventListenerMouse::create();
	switchLaneListener->onMouseDown = CC_CALLBACK_1(GameMaster::switchLaneCallback, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(switchLaneListener, this);

	//create the lane indicator arrow
	arrowIndicatorSprite = Sprite::create("arrow.png");
	//init the arrow position to the mid lane
	arrowIndicatorSprite->setPositionX(awaySpawnPositionX);
	arrowIndicatorSprite->setPositionY(midLaneY);
	arrowIndicatorSprite->setScale(0.2f);
	auto scaleAnimation = ScaleTo::create(0.5f, 0.2f);
	auto scaleAnimation2 = ScaleTo::create(0.5f, 0.3f);
	auto animatedSequence = Sequence::createWithTwoActions(scaleAnimation, scaleAnimation2);
	arrowIndicatorSprite->runAction(RepeatForever::create(animatedSequence));
	this->addChild(arrowIndicatorSprite);

    return true;
}


void GameMaster::clickOnCard(int characterId, int direction) {
	//direction: 0=down, 1=left, 2=right, 3=up
	//spawn the character object
	auto newCharacter = CharacterCreator::getInstance()->charactersFactory(characterId, direction);
	
	auto scene = cocos2d::Director::getInstance()->getRunningScene();
	scene->addChild(newCharacter, 1);

	CCLOG("lane selector: %d", currentLane);

	//check the currentLane flag and then add the character into the corresponding vector
	addCharacterToLane(currentLane, newCharacter, "away");

	CCLOG("The  lane : %d", currentLane);

	//calculate the laneposition
	float LanePositionY;
	switch (currentLane) {
	case laneTop:
		LanePositionY = topLaneY;
		break;
	case laneMid:
		LanePositionY = midLaneY;
		break;
	case laneBot:
		LanePositionY = botLaneY;
		break;
	default:
		LanePositionY = 0;
		break;
	}
	
	//adjust the position of the fucking character
	newCharacter->setPosition(Vec2(awaySpawnPositionX, LanePositionY));

	
	//set the moveto action to the new character
	CCLOG("Current Lane: %d", currentLane);
	CCLOG("LanePositionY=%f", LanePositionY);
	auto characterMoveAction = MoveTo::create(1.2*newCharacter->getSpeed(), Vec2(homeSpawnPositionX, LanePositionY));
	newCharacter->runAction(characterMoveAction);
	CCLOG("Move to %f,%f", homeSpawnPositionX, LanePositionY);
	CCLOG("From %f,%f", newCharacter->getPositionX(), newCharacter->getPositionY());

	
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
			currentLane = laneTop;
			arrowIndicatorSprite->setPositionY(topLaneY);
			CCLOG("Lane switched to top");
			break;
		case 22:
			currentLane = laneMid;
			arrowIndicatorSprite->setPositionY(midLaneY);
			CCLOG("Lane switched to mid");
			break;
		case 26:
			currentLane = laneBot;
			arrowIndicatorSprite->setPositionY(botLaneY);
			CCLOG("Lane switched to bot");
			break;
		default:
			CCLOG("Cannot detect valid GID");
			break;
		}
	}

	CCLOG("The updated lane selector: %d", currentLane);


}

void GameMaster::addSquadToLane(int laneInd, Squad* squad, const std::string& side){
	Vector<Squad*> lane;
	//get the corresponding lane vector
	if (side == "home") {
		lane = getHomeSquadLaneVector(laneInd);
		CCLOG("Gotcha!!! The HOME squad lane vector");

		CCLOG("Added a squad to HomeSquadLaneVector");
	}
	else {
		lane = getAwaySquadLaneVector(laneInd);
		CCLOG("Gotcha!!! The AWAY squad lane vector");


		CCLOG("Added a squad to AwaySquadLaneVector");
	}
    //lane.pushBack(squad);
}

void GameMaster::removeSquadFromLane(int laneInd, Squad* squad, const std::string& side){
	Vector<Squad*> lane;
	//get the corresponding lane vector
	if (side == "home") {
		lane = getHomeSquadLaneVector(laneInd);
		CCLOG("Gotcha!!! The HOME squad lane vector");


		CCLOG("Removed a squad to HomeSquadLaneVector");
	}
	else {
		lane = getAwaySquadLaneVector(laneInd);
		CCLOG("Gotcha!!! The AWAY squad lane vector");


		CCLOG("Removed a squad to AwaySquadLaneVector");
	}
    //lane.erase(lane.find(squad));
}

void GameMaster::addCharacterToLane(int laneInd, Character* character, const std::string& side){
	Vector<Character*> lane;
	//get the corresponding lane vector
	if (side == "home") {
		lane = getHomeCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The HOME character lane vector");
		

		CCLOG("Added a character to HomeCharacterLaneVector");
	}
	else {
		lane = getAwayCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The AWAY character lane vector");


		CCLOG("The up321313dated lane selector: %d", currentLane);
		CCLOG("Added a character to AwayCharacterLaneVector");
	}
	//push the character to the lane vector
    //lane.pushBack(character);
}

void GameMaster::removeCharacterFromLane(int laneInd, Character* character, const std::string& side){
	Vector<Character*> lane;
	//get the corresponding lane vector
	if (side == "home") {
		lane = getHomeCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The HOME character lane vector");


		CCLOG("Removed a character to HomeCharacterLaneVector");
	}
	else {
		lane = getAwayCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The AWAY character lane vector");

		CCLOG("Removed a character to AwayCharacterLaneVector");
	}
	//erase the character to the lane vector
    //lane.erase(lane.find(squad));
}

Vector<Squad*> GameMaster::getHomeSquadLaneVector(int laneIndicator){
    Vector<Squad*> target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = HOME_TOP_SQUAD;
            break;
        case 0:
            target = HOME_MID_SQUAD;
            break;
        case 1:
            target = HOME_BOT_SQUAD;
            break;
    }
    return target;
}

Vector<Character*> GameMaster::getHomeCharacterLaneVector(int laneIndicator) {
	Vector<Character*> target;
	switch (laneIndicator) {
		//-1 top, 0 mid, 1 bot
	case -1:
		target = HOME_TOP_CHARACTER;
		break;
	case 0:
		target = HOME_MID_CHARACTER;
		break;
	case 1:
		target = HOME_BOT_CHARACTER;
		break;
	}
	return target;
}

Vector<Squad*> GameMaster::getAwaySquadLaneVector(int laneIndicator) {
	Vector<Squad*> target;
	switch (laneIndicator) {
		//-1 top, 0 mid, 1 bot
	case -1:
		target = AWAY_TOP_SQUAD;
		break;
	case 0:
		target = AWAY_MID_SQUAD;
		break;
	case 1:
		target = AWAY_BOT_SQUAD;
		break;
	}
	return target;
}

Vector<Character*> GameMaster::getAwayCharacterLaneVector(int laneIndicator){
    Vector<Character*> target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = AWAY_TOP_CHARACTER;
            break;
        case 0:
            target = AWAY_MID_CHARACTER;
            break;
        case 1:
            target = AWAY_BOT_CHARACTER;
            break;
    }
    return target;
}

void GameMaster::checkCollision(){
	
}
