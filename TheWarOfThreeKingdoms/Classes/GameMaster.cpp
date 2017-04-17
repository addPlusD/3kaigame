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

////GameMaster* GameMaster::createMaster(){
////    //return GameMaster::create();
////	gameMaster = GameMaster::create();
////	return gameMaster;
////}

GameMaster* GameMaster::getInstance() {
	if (!isCreated) {
		isCreated = true;
		gameMaster = new GameMaster();
		if (gameMaster && gameMaster->init()) {
			gameMaster->autorelease();
			return gameMaster;
		}
		CC_SAFE_DELETE(gameMaster);
	}
	return gameMaster;
}

GameMaster::GameMaster() {
	HOME_TOP_SQUAD = Vector<Squad*>{ 10 };
	HOME_MID_SQUAD = Vector<Squad*>{ 10 };
	HOME_BOT_SQUAD = Vector<Squad*>{ 10 };
	 AWAY_TOP_SQUAD = Vector<Squad*>{ 10 };
	 AWAY_MID_SQUAD = Vector<Squad*>{ 10 };
	 AWAY_BOT_SQUAD = Vector<Squad*>{ 10 };
	 HOME_TOP_CHARACTER = Vector<Character*>{ 10 };
	 HOME_MID_CHARACTER = Vector<Character*>{ 10 };
	 HOME_BOT_CHARACTER = Vector<Character*>{ 10 };
	 AWAY_TOP_CHARACTER = Vector<Character*>{ 10 };
	 AWAY_MID_CHARACTER = Vector<Character*>{ 10 };
	 AWAY_BOT_CHARACTER = Vector<Character*>{ 10 };
}

GameMaster::~GameMaster() {
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

	currentLane = laneMid;
    return true;
	
}


void GameMaster::clickOnCard(int characterId, int direction) {
	//direction: 0=down, 1=left, 2=right, 3=up
	//spawn the character object
	auto newCharacter = CharacterCreator::getInstance()->charactersFactory(characterId, direction);
	
	auto scene = cocos2d::Director::getInstance()->getRunningScene();
	scene->addChild(newCharacter, 1);

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
	//auto characterMoveAction = MoveTo::create(1.2*newCharacter->getSpeed(), Vec2(homeSpawnPositionX, LanePositionY));
	//newCharacter->moveTo = characterMoveAction;
	newCharacter->moveTo = MoveTo::create(1.2*newCharacter->getSpeed(), Vec2(homeSpawnPositionX, LanePositionY));
	newCharacter->runAction(newCharacter->moveTo);
	CCLOG("Move to %f,%f", homeSpawnPositionX, LanePositionY);
	CCLOG("From %f,%f", newCharacter->getPositionX(), newCharacter->getPositionY());

	//check the currentLane flag and then add the character into the corresponding vector
	addCharacterToLane(currentLane, newCharacter, "away");
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
    lane.pushBack(squad);
	CCLOG("Added!");
	CCLOG("There are %d elements in the lane", lane.size());
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
    lane.erase(lane.find(squad));
	CCLOG("Erased!");
	CCLOG("There are %d elements in the lane", lane.size());
}

void GameMaster::addCharacterToLane(int laneInd, Character* character, const std::string& side){
	Vector<Character*>* lane;
	//get the corresponding lane vector
	if (side == "home") {
		lane = getHomeCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The HOME character lane vector");
		

		CCLOG("Added a character to HomeCharacterLaneVector");
	}
	else {
		lane =getAwayCharacterLaneVector(laneInd);
		CCLOG("Gotcha!!! The AWAY character lane vector");


		CCLOG("Added a character to AwayCharacterLaneVector");
	}
	lane->reserve(1);
	//push the character to the lane vector
    lane->pushBack(character);

	CCLOG("Added!");
	CCLOG("There are %d elements in the lane", lane->size());
//	CCLOG("testing mid::::There are %d elements in the lane", AWAY_MID_CHARACTER.size());
//	CCLOG("testing top::::There are %d elements in the lane", AWAY_TOP_CHARACTER.size());
	CCLOG("There are %d elements in the lane", lane->capacity());
}

void GameMaster::removeCharacterFromLane(int laneInd, Character* character, const std::string& side){ //not test
	Vector<Character*>* lane;
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
    lane->erase(lane->find(character));
	CCLOG("Erased!");
	CCLOG("There are %d elements in the lane", lane->size());
	CCLOG("There are %d elements in the lane", lane->capacity());
}

Vector<Squad*> GameMaster::getHomeSquadLaneVector(int laneIndicator){
    Vector<Squad*> target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = HOME_TOP_SQUAD;
			CCLOG("Returned Squad Home Top");
            break;
        case 0:
            target = HOME_MID_SQUAD;
			CCLOG("Returned Squad Home Mid");
            break;
        case 1:
            target = HOME_BOT_SQUAD;
			CCLOG("Returned Squad Home Bot");
            break;
    }
    return target;
}

Vector<Character*>* GameMaster::getHomeCharacterLaneVector(int laneIndicator) {
	Vector<Character*>* target;
	switch (laneIndicator) {
		//-1 top, 0 mid, 1 bot
	case -1:
		target = &HOME_TOP_CHARACTER;
		CCLOG("Returned Character Home Top");
		break;
	case 0:
		target = &HOME_MID_CHARACTER;
		CCLOG("Returned Character Home Mid");
		break;
	case 1:
		target = &HOME_BOT_CHARACTER;
		CCLOG("Returned Character Home Bot");
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
		CCLOG("Returned Squad Away Top");
		break;
	case 0:
		target = AWAY_MID_SQUAD;
		CCLOG("Returned Squad Away Mid");
		break;
	case 1:
		target = AWAY_BOT_SQUAD;
		CCLOG("Returned Squad Away Bot");
		break;
	}
	return target;
}

Vector<Character*>* GameMaster::getAwayCharacterLaneVector(int laneIndicator){
    Vector<Character*>* target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = &AWAY_TOP_CHARACTER;
			CCLOG("Returned Character Away Top");
            break;
        case 0:
            target = &AWAY_MID_CHARACTER;
			CCLOG("Returned Character Away Mid");
            break;
        case 1:
            target = &AWAY_BOT_CHARACTER;
			CCLOG("Returned Character Away Bot");
            break;
    }
    return target;
}

void GameMaster::checkCollision(){
	
}

void GameMaster::update(float delta) {
	//do the update job here

	//vector<Character*>::iterator iter;
	//for (iter = AWAY_TOP_CHARACTER.begin(); iter != AWAY_TOP_CHARACTER.end(); iter++) {
	//	CCLOG("update character"); 
	//}

	//CCLOG("updating master");
	//AWAY_TOP_CHARACTER
	//CCLOG("ai size: %d", HOME_TOP_CHARACTER.size());
	//for (auto *playerCharacter : AWAY_TOP_CHARACTER) // access by reference to avoid copying
	//{
	//	if (HOME_TOP_CHARACTER.size() != 0) {
	//		for (auto *aiCharacter : HOME_TOP_CHARACTER) {
	//			playerCharacter->findEnemyWithinRange(aiCharacter);
	//			if (aiCharacter->health < 0) {
	//				aiCharacter->die();
	//				//HOME_TOP_CHARACTER.eraseObject(aiCharacter);
	//				//removeCharacterFromLane(-1, aiCharacter, "home");
	//			}
	//		}
	//	}
	//}

	for (vector<Character*>::iterator pit = AWAY_TOP_CHARACTER.begin();pit != AWAY_TOP_CHARACTER.end();)
	{


		for (vector<Character*>::iterator ait = HOME_TOP_CHARACTER.begin(); ait != HOME_TOP_CHARACTER.end();) {
			(*pit)->findEnemyWithinRange((*ait));
			//CCLOG("home top: %d", HOME_TOP_CHARACTER.size());
			if ((*ait)->health<0) {
				(*ait)->die();
				ait = HOME_TOP_CHARACTER.erase(ait);
				//(*pit)->runAction((*pit)->moveTo);
			}
			else {
				++ait;
			}
		}
		++pit;
	}



	//cocos2d::Vector<Character*> HOME_TOP_CHARACTER;
	//cocos2d::Vector<Character*> HOME_MID_CHARACTER;
	//cocos2d::Vector<Character*> HOME_BOT_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_TOP_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_MID_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_BOT_CHARACTER;
}
