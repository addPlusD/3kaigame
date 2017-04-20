//
//  GameMaster.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameMaster.h"
#include "MainMenuScene.h"


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
		gameMaster = new GameMaster();
		if (gameMaster && gameMaster->init()) {
            isCreated = true;
			gameMaster->autorelease();
			return gameMaster;
		}
		CC_SAFE_DELETE(gameMaster);
	}
	return gameMaster;
}

GameMaster::GameMaster() {
}

GameMaster::~GameMaster() {
}


bool GameMaster::init(){
    if(!Layer::init()){
        return false;
    }
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("BG.mp3");
	audio->playBackgroundMusic("BG.mp3");
	audio->setEffectsVolume(1.0f);

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto costBar = Bar::create(5);
    costBar->setScale(1,0.6);
    costBar->setPosition(Vec2(origin.x + visibleSize.width - costBar->getContentSize().width / 2,
                              origin.y + visibleSize.height - costBar->getContentSize().height / 2));
    costBar->setTag(201);
    this->addChild(costBar, 1);
    
    auto costBarLabel = Label::createWithTTF("Cost Bar", "fonts/Marker Felt.ttf", 32);
    costBarLabel ->setPosition(Vec2(costBarLabel->getContentSize().width-costBar->getContentSize().width/2,costBar->getContentSize().height / 2));
    costBar->addChild(costBarLabel);
    
    this->schedule(schedule_selector(GameMaster::recoverCost),5.0f);
    
    
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)->void{
        if (keyCode==EventKeyboard::KeyCode::KEY_SPACE) {
            if (this->isPause) {
                Director::getInstance()->resume();
            }else{
                Director::getInstance()->pause();
            }
            this->isPause=!this->isPause;
        }
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
    
	currentLane = laneMid;
    return true;
	
}

void GameMaster::setCost(int diff){
    this->cost+=diff;
}

void GameMaster::recoverCost(float dt){
    auto costBar = (Bar*)this->getChildByTag(201);
    
    if (this->cost<costBar->getMaxHP()){
        this->cost+=1;
    }
}

int GameMaster::getCost(){
    return this->cost;
}


void GameMaster::clickOnCard(int characterId, int direction) {
	//direction: 0=down, 1=left, 2=right, 3=up
	//spawn the character object
    if (this->getCost()<1){
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

		audio->playEffect("negative.wav");
        return;
    }
    
	if (!cardCoolDown) {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

		audio->playEffect("misc_menu_4.wav");

		auto newCharacter = CharacterCreator::getInstance()->charactersFactory(characterId, direction);

		auto scene = cocos2d::Director::getInstance()->getRunningScene()->getChildByTag(999);
		scene->addChild(newCharacter, 1);

		//set the side of the character
		newCharacter->setSide("away");
		newCharacter->setLane(currentLane);
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

		//create the action for the sprites
		createAction(newCharacter);

		//CCLOG("Move to %f,%f", homeSpawnPositionX, LanePositionY);
		//CCLOG("From %f,%f", newCharacter->getPositionX(), newCharacter->getPositionY());

		//check the currentLane flag and then add the character into the corresponding vector
		addCharacterToLane(currentLane, newCharacter, "away");
		cardCoolDown = true;
        this->setCost(-1);
	}
	else {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

		audio->playEffect("negative.wav");
		return;
	}
}

//dunt know what is character, tell GameMaster in header(include the Character.h)
void GameMaster::createAction(Character* target) {

	//check the side, then assign different coordinate
	float destinationX;
	if (target->getSide() == "away") {
		destinationX = homeSpawnPositionX;

	}
	else {
		destinationX = awaySpawnPositionX;
	}

	//set the moveto action to the new character
	auto characterMoveAction = MoveTo::create(1.2*target->getSpeed(), Vec2(destinationX, target->getPositionY()));


	CCLOG("init duration:%f", 1.2*target->getSpeed());

	//set the duration to action for later resume
	target->setPassedActionDuration(1.2*target->getSpeed());

	//newCharacter->moveTo = characterMoveAction;
	//newCharacter->moveTo = MoveTo::create(1.2*newCharacter->getSpeed(), Vec2(homeSpawnPositionX, LanePositionY));
	//newCharacter->runAction(newCharacter->moveTo);
	//target->setMoveAction(characterMoveAction);

	//set the finish callback to new character
	auto characterCallbackAction = CallFuncN::create(CC_CALLBACK_1(GameMaster::minionArriveTowerCallback, this));

	//set the action sequence to new character, later you just only need to rerun this sequence by character->runAction();

	auto runSequence = Sequence::create(characterMoveAction, characterCallbackAction, nullptr);
	target->setActionSequence(runSequence);

	target->runAction(runSequence);
	target->startPathing();

}


void GameMaster::resumeAction(Character* target) {
	//check the side, then assign different coordinate
	float destinationX;
	if (target->getSide() == "away") {
		destinationX = homeSpawnPositionX;
	}
	else {
		destinationX = awaySpawnPositionX;
	}

	//set the moveto action based on passed duration to the new character
	auto characterMoveAction = MoveTo::create(target->getPassedActionDuration(), Vec2(destinationX, target->getPositionY()));

	CCLOG("Resume duration:%f", target->getPassedActionDuration());

	//set the finish callback to new character
	auto characterCallbackAction = CallFuncN::create(CC_CALLBACK_1(GameMaster::minionArriveTowerCallback, this ));

	auto runSequence = Sequence::create(characterMoveAction, characterCallbackAction, nullptr);
	target->setActionSequence(runSequence);

	target->runAction(runSequence);

	//resume the walking
	target->startPathing();
}

//implement the switch lane command click
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
	std::vector<Squad*>* lane;
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
    lane->push_back(squad);
	CCLOG("Added!");
	CCLOG("There are %ld elements in the lane", lane->size());
}

void GameMaster::removeSquadFromLane(int laneInd, Squad* squad, const std::string& side){
	std::vector<Squad*>* lane;
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
	lane->erase(std::remove(lane->begin(), lane->end(), squad), lane->end());
	CCLOG("Erased!");
	CCLOG("There are %ld elements in the lane", lane->size());
}

void GameMaster::addCharacterToLane(int laneInd, Character* character, const std::string& side){
	std::vector<Character*>* lane;
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
	//push the character to the lane vector
    lane->push_back(character);

	CCLOG("Added!");
	CCLOG("There are %ld elements in the lane", lane->size());
//	CCLOG("testing mid::::There are %d elements in the lane", AWAY_MID_CHARACTER.size());
//	CCLOG("testing top::::There are %d elements in the lane", AWAY_TOP_CHARACTER.size());
}

void GameMaster::removeCharacterFromLane(int laneInd, Character* character, const std::string& side){ //not test
	std::vector<Character*>* lane;
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
    lane->erase(std::remove(lane->begin(), lane->end(), character), lane->end());
	CCLOG("Erased!");
	CCLOG("There are %ld elements in the lane", lane->size());
}

std::vector<Squad*>* GameMaster::getHomeSquadLaneVector(int laneIndicator){
	std::vector<Squad*>* target;
    switch(laneIndicator){
            //-1 top, 0 mid, 1 bot
        case -1:
            target = &HOME_TOP_SQUAD;
			CCLOG("Returned Squad Home Top");
            break;
        case 0:
            target = &HOME_MID_SQUAD;
			CCLOG("Returned Squad Home Mid");
            break;
        case 1:
            target = &HOME_BOT_SQUAD;
			CCLOG("Returned Squad Home Bot");
            break;
    }
    return target;
}

std::vector<Character*>* GameMaster::getHomeCharacterLaneVector(int laneIndicator) {
	std::vector<Character*>* target;
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

std::vector<Squad*>* GameMaster::getAwaySquadLaneVector(int laneIndicator) {
	std::vector<Squad*>* target;
	switch (laneIndicator) {
		//-1 top, 0 mid, 1 bot
	case -1:
		target = &AWAY_TOP_SQUAD;
		CCLOG("Returned Squad Away Top");
		break;
	case 0:
		target = &AWAY_MID_SQUAD;
		CCLOG("Returned Squad Away Mid");
		break;
	case 1:
		target = &AWAY_BOT_SQUAD;
		CCLOG("Returned Squad Away Bot");
		break;
	}
	return target;
}

std::vector<Character*>* GameMaster::getAwayCharacterLaneVector(int laneIndicator){
	std::vector<Character*>* target;
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

void GameMaster::minionArriveTowerCallback(Node* sender) {
	Tower* targetTower;
	
	Character* character = (Character*)sender;
	if (character->getSide() == "away") {
		targetTower = (Tower*)Director::getInstance()->getRunningScene()->getChildByTag(999)->getChildByName("homeTower");
	}
	else {
		targetTower = (Tower*)Director::getInstance()->getRunningScene()->getChildByTag(999)->getChildByName("awayTower");
	}
	CCLOG("Character %s reaches the end, deal %d damage", character->getName().c_str(), character->getAttackDamage());
	removeCharacterFromLane(character->getLane(), character, character->getSide());
	targetTower->takeDamage(character);
	character->die();
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


	Vector<Character*> homeTBDTopVector;
	Vector<Character*> awayTBDTopVector;
	Vector<Character*> homeTBDMidVector;
	Vector<Character*> awayTBDMidVector;
	Vector<Character*> homeTBDBotVector;
	Vector<Character*> awayTBDBotVector;
    
    //update cost bar
    auto costBar = (Bar*)this->getChildByTag(201);
    costBar->updateHP(this->getCost());
	
	//Eddie on 20170418
	//Handle top collision (Player attack turn)
	for (Character* player : AWAY_TOP_CHARACTER) {
		bool playerFoundEnemy = false;
		//hit the tower first if the character can
		/*if (homeTower->findMinionArrived(player)) {
			playerFoundEnemy = true;
			homeTower->takeDamage(player);
		}*/
		//if no tower nearby find the enemy
		for (Character* ai : HOME_TOP_CHARACTER) {
			//player tries to attack the ai
			if (player->findEnemyWithinRange(ai)) {
				//do not let the player resumeAction
				playerFoundEnemy = true;
				//check ai's health
				if (ai->getHealth() <= 0) {
					CCLOG("Player killed the AI with damage %d", player->getAttackDamage());
					//ai dies
					ai->die();
					//add the object to TO BE DELETED vector
					homeTBDTopVector.pushBack(ai);
					//remove ai from the lane vector
					//removeCharacterFromLane(laneTop, ai, "home");
					CCLOG("AI dies!");
					//resume action for player
					//resumeAction(player);
				}
				break;
			}
		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!playerFoundEnemy && player->isStopped()) {
			resumeAction(player);
			player->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : homeTBDTopVector) {
		removeCharacterFromLane(laneTop, character, "home");
	}


	//Handle top collision (AI attack turn)
	for (Character* ai : HOME_TOP_CHARACTER) {
		bool aiFoundEnemy = false;
		//hit the tower first if the character can
		/*if (awayTower->findMinionArrived(ai)) {
			aiFoundEnemy = true;
			awayTower->takeDamage(ai);
		}*/
		//if no tower nearby find the enemy
		for (Character* player : AWAY_TOP_CHARACTER) {
			//ai tries to attack the player
			if (ai->findEnemyWithinRange(player)) {
				//do not let the player resumeAction
				aiFoundEnemy = true;
				//check player's health
				if (player->getHealth() <= 0) {
					CCLOG("AI killed the player with damage %d", ai->getAttackDamage());
					//stop player action
					player->stopAction(player->getActionSequence());
					//player dies
					player->die();
					//add the object to TO BE DELETED vector
					awayTBDTopVector.pushBack(player);
					//remove player from the lane vector
					//removeCharacterFromLane(laneTop, player, "away");
					CCLOG("Player dies!");
					//resume action for ai(later remove the comment)
					//resumeAction(ai);
					break;
				}
			}

		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!aiFoundEnemy && ai->isStopped()) {
			resumeAction(ai);
			ai->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : awayTBDTopVector) {
		removeCharacterFromLane(laneTop, character, "away");
	}



	//Handle mid collision (Player attack turn)
	for (Character* player : AWAY_MID_CHARACTER) {
		bool playerFoundEnemy = false;
		//hit the tower first if the character can
		/*if (homeTower->findMinionArrived(player)) {
			playerFoundEnemy = true;
			homeTower->takeDamage(player);
		}*/
		//if no tower nearby find the enemy
		for (Character* ai : HOME_MID_CHARACTER) {
			//player tries to attack the ai
			if (player->findEnemyWithinRange(ai)) {
				//do not let the player resumeAction
				playerFoundEnemy = true;
				//check ai's health
				if (ai->getHealth() <= 0) {
					CCLOG("Player killed the AI with damage %d", player->getAttackDamage());
					//ai dies
					ai->die();
					//add the object to TO BE DELETED vector
					homeTBDMidVector.pushBack(ai);
					//remove ai from the lane vector
					//removeCharacterFromLane(laneTop, ai, "home");
					CCLOG("AI dies!");
					//resume action for player
					//resumeAction(player);
				}
				break;
			}
		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!playerFoundEnemy && player->isStopped()) {
			resumeAction(player);
			player->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : homeTBDMidVector) {
		removeCharacterFromLane(laneMid, character, "home");
	}


	//Handle mid collision (AI attack turn)
	for (Character* ai : HOME_MID_CHARACTER) {
		bool aiFoundEnemy = false;
		//hit the tower first if the character can
		/*if (awayTower->findMinionArrived(ai)) {
			aiFoundEnemy = true;
			awayTower->takeDamage(ai);
		}*/
		//if no tower nearby find the enemy
		for (Character* player : AWAY_MID_CHARACTER) {
			//ai tries to attack the player
			if (ai->findEnemyWithinRange(player)) {
				//do not let the player resumeAction
				aiFoundEnemy = true;
				//check player's health
				if (player->getHealth() <= 0) {
					CCLOG("AI killed the player with damage %d", ai->getAttackDamage());
					//stop player action
					player->stopAction(player->getActionSequence());
					//player dies
					player->die();
					//add the object to TO BE DELETED vector
					awayTBDMidVector.pushBack(player);
					//remove player from the lane vector
					//removeCharacterFromLane(laneTop, player, "away");
					CCLOG("Player dies!");
					//resume action for ai(later remove the comment)
					//resumeAction(ai);
					break;
				}
			}

		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!aiFoundEnemy && ai->isStopped()) {
			resumeAction(ai);
			ai->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : awayTBDMidVector) {
		removeCharacterFromLane(laneMid, character, "away");
	}



	//Handle bot collision (Player attack turn)
	for (Character* player : AWAY_BOT_CHARACTER) {
		bool playerFoundEnemy = false;
		for (Character* ai : HOME_BOT_CHARACTER) {
			//player tries to attack the ai
			if (player->findEnemyWithinRange(ai)) {
				//do not let the player resumeAction
				playerFoundEnemy = true;
				//check ai's health
				if (ai->getHealth() <= 0) {
					CCLOG("Player killed the AI with damage %d", player->getAttackDamage());
					//ai dies
					ai->die();
					//add the object to TO BE DELETED vector
					homeTBDBotVector.pushBack(ai);
					//remove ai from the lane vector
					//removeCharacterFromLane(laneTop, ai, "home");
					CCLOG("AI dies!");
					//resume action for player
					//resumeAction(player);
				}
				break;
			}
		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!playerFoundEnemy && player->isStopped()) {
			resumeAction(player);
			player->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : homeTBDBotVector) {
		removeCharacterFromLane(laneBot, character, "home");
	}


	//Handle bot collision (AI attack turn)
	for (Character* ai : HOME_BOT_CHARACTER) {
		bool aiFoundEnemy = false;
		for (Character* player : AWAY_BOT_CHARACTER) {
			//ai tries to attack the player
			if (ai->findEnemyWithinRange(player)) {
				//do not let the player resumeAction
				aiFoundEnemy = true;
				//check player's health
				if (player->getHealth() <= 0) {
					CCLOG("AI killed the player with damage %d", ai->getAttackDamage());
					//stop player action
					player->stopAction(player->getActionSequence());
					//player dies
					player->die();
					//add the object to TO BE DELETED vector
					awayTBDBotVector.pushBack(player);
					//remove player from the lane vector
					//removeCharacterFromLane(laneTop, player, "away");
					CCLOG("Player dies!");
					//resume action for ai(later remove the comment)
					//resumeAction(ai);
					break;
				}
			}

		}
		//if this round did not find any enemy, and player is not in action(may be due to last round hit)
		//then resume its action
		if (!aiFoundEnemy && ai->isStopped()) {
			resumeAction(ai);
			ai->setStopped(false);
		}
	}

	//remove all the fucking elements in the TO BE DELETED vector, becoz they can't be erased inside the iteration
	for (Character* character : awayTBDBotVector) {
		removeCharacterFromLane(laneBot, character, "away");
	}

	if (cardCoolDown) {
		this->timeStamp += delta;
	}

	if (timeStamp > 1) {
		cardCoolDown = false;
		timeStamp = 0;
	}
	//for (std::vector<Character*>::iterator player = AWAY_TOP_CHARACTER.begin(); player != AWAY_TOP_CHARACTER.end();)
	//{
	//	for (std::vector<Character*>::iterator ai = HOME_TOP_CHARACTER.begin(); ai != HOME_TOP_CHARACTER.end();) {
	//		//player tries to attack the ai
	//		(*player)->findEnemyWithinRange(*ai);
	//		//check ai's health
	//		if ((*ai)->getHealth() <= 0) {
	//			CCLOG("Player killed the AI with damage %d", (*player)->getAttackDamage());
	//			//ai dies
	//			(*ai)->die();
	//			//remove ai from the lane vector
	//			//removeCharacterFromLane(laneTop, *ai, "home");
	//			CCLOG("AI dies!");
	//			//resume action for player
	//			resumeAction(*player);
	//			continue;
	//		}

	//		//ai tries to attack the player
	//		(*ai)->findEnemyWithinRange(*player);
	//		//check player's health
	//		if ((*player)->getHealth() <= 0) {
	//			CCLOG("AI killed the player with damage %d", (*ai)->getAttackDamage());
	//			//stop player action
	//			(*player)->stopAction((*player)->getActionSequence());
	//			//player dies
	//			(*player)->die();
	//			//remove player from the lane vector
	//			//removeCharacterFromLane(laneTop, *player, "away");
	//			CCLOG("Player dies!");
	//			//resume action for ai
	//			//resumeAction(ai);
	//			break;
	//		}
	//		++ai;
	//	}
	//	++player;
	//}

    //
    
    /* Bon's collision
	for (vector<Character*>::iterator player = AWAY_TOP_CHARACTER.begin();pit != AWAY_TOP_CHARACTER.end();)
	{
		for (vector<Character*>::iterator ai = HOME_TOP_CHARACTER.begin(); ait != HOME_TOP_CHARACTER.end();) {
			(*player)->findEnemyWithinRange((*ai));
			//CCLOG("home top: %d", HOME_TOP_CHARACTER.size());
			if ((*ai)->health<0) {
				(*ai)->die();
				ait = HOME_TOP_CHARACTER.erase(ait);
                performAction(*pit);
			}
			else {
				++ait;
			}
		}
		//(*pit)->runAction((*pit)->moveTo);
		++pit;
	}

	for (vector<Character*>::iterator ait = HOME_TOP_CHARACTER.begin(); ait != HOME_TOP_CHARACTER.end();)
	{
		for (vector<Character*>::iterator pit = AWAY_TOP_CHARACTER.begin(); pit != AWAY_TOP_CHARACTER.end();) {
			(*ait)->findEnemyWithinRange((*pit));
			//CCLOG("home top: %d", HOME_TOP_CHARACTER.size());
			if ((*pit)->health<0) {
				(*pit)->die();
				pit = AWAY_TOP_CHARACTER.erase(pit);
			}
			else {
				++pit;
			}
		}
		++ait;
	}
     */

	//cocos2d::Vector<Character*> HOME_TOP_CHARACTER;
	//cocos2d::Vector<Character*> HOME_MID_CHARACTER;
	//cocos2d::Vector<Character*> HOME_BOT_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_TOP_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_MID_CHARACTER;
	//cocos2d::Vector<Character*> AWAY_BOT_CHARACTER;
    
    //AI time for generating new character
    this->timeSpent+=delta;
    
    setAi(timeSpent);
}

void GameMaster::setAi(float time){
    
    if (!aiStart) {
        GameAi::getInstance()->init(this->lv);
        aiStart=true;
    }else if (time>6){
        GameAi::getInstance()->update();
        
        //reset time for next 4 seconds
        this->timeSpent=0;
    }
}

std::vector<Character*> GameMaster::getAwayCharacter(int lane){
    // top =0, mid =1, bot =2;
    switch (lane) {
        case 0:
            return AWAY_TOP_CHARACTER;
            break;
        case 1:
            return AWAY_MID_CHARACTER;
            break;
        case 2:
            return AWAY_BOT_CHARACTER;
            break;
    }
    
}

void GameMaster::createAiAction(Character* target){
    //set the moveto action to the new character
    auto characterMoveAction = MoveTo::create(1.2*target->getSpeed(), Vec2(awaySpawnPositionX, target->getPositionY()));
    
    CCLOG("init duration:%f",1.2*target->getSpeed());
    
    //set the duration to action for later resume
    target->setPassedActionDuration(1.2*target->getSpeed());
    
    
    auto runSequence = Sequence::create(characterMoveAction, nullptr);
    target->setActionSequence(runSequence);
    
    target->runAction(runSequence);
    target->startPathing();
    
}

void GameMaster::setLV(int LV){
    this->lv = LV;
    CCLOG("lv %d",LV);
}

