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

	layer->setTag(999);
	scene->addChild(layer);

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

	auto test1= Character::createCharacter("moveCharacter2.png", 2);
	test1->setPosition(Vec2(200, 650));
	test1->setProperty(200, 500, 50, 0, 2);
	this->addChild(test1,1);
    test1->setName("test1");
	//test1->health = 1000;
	GameMaster::getInstance()->addCharacterToLane(-1, test1, "home");

	auto test2 = Character::createCharacter("moveCharacter3.png", 2);
	test2->setPosition(Vec2(100, 650));
	test2->setProperty(1000, 50, 20, 0, 2);
	this->addChild(test2, 1);
	test2->setHealth(1000);
    test2->setName("test2");
	GameMaster::getInstance()->addCharacterToLane(-1, test2, "home");
//	GameMaster::getInstance()->removeCharacterFromLane(0, test1, "away");



	//tell program to do update
	scheduleUpdate();
	GameMaster::getInstance()->scheduleUpdate();
	return true;
}

//Implementing update member function of class GameWorld
void GameWorld::update(float delta) {
    gameMaster->update(delta);
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

	/*auto castle = Sprite::create("castle.png");
	castle->setPosition(Vec2(origin.x + visibleSize.width - castle->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + castle->getContentSize().height / 2));
	this->addChild(castle, 1);

	auto enemyCastle = Sprite::create("enemy_castle.png");
	enemyCastle->setPosition(Vec2(origin.x + enemyCastle->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + enemyCastle->getContentSize().height / 2));
	this->addChild(enemyCastle, 1);*/

	auto castle = Tower::createTower("castle.png", towerHP);
	castle->setPosition(Vec2(origin.x + visibleSize.width - castle->getContentSize().width / 2, origin.y + visibleSize.height / 2 + castle->getContentSize().height / 2));
	castle->setName("awayTower");
	this->addChild(castle);
	


	auto enemyCastle = Tower::createTower("enemy_castle.png", towerHP);
	enemyCastle->setPosition(Vec2(origin.x + enemyCastle->getContentSize().width / 2, origin.y + visibleSize.height / 2 + enemyCastle->getContentSize().height / 2));
	//set the bounding box of the tower;
	enemyCastle->setName("homeTower");
	this->addChild(enemyCastle);
	
    
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
}

void GameWorld::setHP() {
    auto castleHP = (Bar*)getChildByTag(100);
    castleHP->updateHP(castle);
    
    auto enemyCastleHP = (Bar*)getChildByTag(101);
    enemyCastleHP->updateHP(enemyCastle);
}

