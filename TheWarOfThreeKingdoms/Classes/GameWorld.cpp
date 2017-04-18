//
//  GameWorld.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameWorld.h"
#include "ui/CocosGUI.h"
#include "Bar.h"

USING_NS_CC;
using namespace ui;

int castle = 1000,enemyCastle = 1000;

//Implementing createScene member function of class GameWorld
Scene* GameWorld::createScene() {
	auto scene = Scene::create();

	auto layer = GameWorld::create();

	scene->addChild(layer, 1, 999);

	return scene;
}

GameWorld::~GameWorld() {
}

//Implementing init member function of class GameWorld
bool GameWorld::init() {
	//do the init job here

	if (!Layer::init())
	{
		return false;
	}

	/*auto character = Character::createCharacter("moveCharacter1.png");
	this->addChild(character, 1);*/
	
	setBackground();
	setCards();
	setMaster();

	auto test1= Character::createCharacter("moveCharacter2.png", 1);
	test1->setPosition(Vec2(200, 650));
	test1->setProperty(200, 500, 50, 0);
	this->addChild(test1,1);
	//test1->health = 1000;
	GameMaster::getInstance()->addCharacterToLane(-1, test1, "home");

	auto test2 = Character::createCharacter("moveCharacter3.png", 1);
	test2->setPosition(Vec2(100, 650));
	test2->setProperty(1000, 50, 20, 0);
	this->addChild(test2, 1);
	test2->health = 1000;
	GameMaster::getInstance()->addCharacterToLane(-1, test2, "home");
//	GameMaster::getInstance()->removeCharacterFromLane(0, test1, "away");


	//Below code for debug purpose
	auto label = Label::create("", "Arial", 50.0);
	label->setPosition(300, 700);
	this->addChild(label);
	label->setColor(Color3B::RED);
	label->setName("debugLabel");
	auto _mouseEventListener = EventListenerMouse::create();
	_mouseEventListener->onMouseMove = [&](Event* event) -> void {
		EventMouse* e = (EventMouse*)event;
		auto label = (Label*)this->getChildByName("debugLabel");
		char buffer[256] = { 0 };
		sprintf(buffer, "x: %f, y: %f", e->getCursorX(), e->getCursorY());
		label->setString(buffer);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseEventListener, this);

	//tell program to do update
	scheduleUpdate();
	GameMaster::getInstance()->scheduleUpdate();
	return true;
}

//Implementing update member function of class GameWorld
void GameWorld::update(float delta) {
	//do the update job here
	//CCLOG("updating game world");
	//GameMaster::getInstance()->checkCollision();
    setHP();
}

void GameWorld::setMaster() {
	gameMaster = GameMaster::getInstance();
	this->addChild(gameMaster);
	CCLOG("Reference count of the master: %d", gameMaster->getReferenceCount());
}

void GameWorld::setCards() {
    
    auto card1 = Card::create("character1.png",0,0);
    this->addChild(card1, 1);
    
    auto card2 = Card::create("character2.png", 1, 1);
    this->addChild(card2, 1);
    
    auto card3 = Card::create("arrow.png", 2, 2);
    this->addChild(card3, 1);
    
    auto card4 = Card::create("horse.png", 3, 3);
    this->addChild(card4, 1);
    
    auto card5 = Card::create("soldier.png", 4, 4);
    this->addChild(card5, 1);
    
}

void GameWorld::setBackground() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tileMap = TMXTiledMap::create("AIGame_map.tmx");
	//    auto background = tileMap->layerNamed("Background");
	tileMap->setName("GameMap"); 
	this->addChild(tileMap);

	auto castle = Sprite::create("castle.png");
	castle->setPosition(Vec2(origin.x + visibleSize.width - castle->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + castle->getContentSize().height / 2));
	this->addChild(castle, 1);

	auto enemyCastle = Sprite::create("enemy_castle.png");
	enemyCastle->setPosition(Vec2(origin.x + enemyCastle->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + enemyCastle->getContentSize().height / 2));
	this->addChild(enemyCastle, 1);
    
    auto castleHP = Bar::create(1000);
    castleHP->setScale(0.3);
    castleHP->setPosition(Vec2(origin.x + visibleSize.width - castle->getContentSize().width / 2+5,
                               origin.y + visibleSize.height / 2 + castle->getContentSize().height / 2+40));

    castleHP->setTag(100);
    this->addChild(castleHP, 1);
    
    auto enemyCastleHP = Bar::create(1000);
    enemyCastleHP->setScale(0.3);
    enemyCastleHP->setPosition(Vec2(origin.x + enemyCastle->getContentSize().width / 2+5,
                                    origin.y + visibleSize.height / 2 + enemyCastle->getContentSize().height / 2 +40));
    enemyCastleHP->setTag(101);
    this->addChild(enemyCastleHP, 1);
    
    auto costBar = Bar::create(5);
    costBar->setScale(1,0.6);
    costBar->setPosition(Vec2(origin.x + visibleSize.width - costBar->getContentSize().width / 2,
                               origin.y + visibleSize.height - costBar->getContentSize().height / 2));
    costBar->setTag(201);
    this->addChild(costBar, 1);
    
    auto enemyCostBar = Bar::create(5);
    enemyCostBar->setScale(1,0.6);
    enemyCostBar->setPosition(Vec2(origin.x + enemyCostBar->getContentSize().width  / 2,
                              origin.y + visibleSize.height - enemyCostBar->getContentSize().height / 2));
    enemyCostBar->setTag(202);
    this->addChild(enemyCostBar, 1);
}

void GameWorld::setHP() {
    auto castleHP = (Bar*)getChildByTag(100);
    castleHP->updateHP(castle);
    
    auto enemyCastleHP = (Bar*)getChildByTag(101);
    enemyCastleHP->updateHP(enemyCastle);
}

