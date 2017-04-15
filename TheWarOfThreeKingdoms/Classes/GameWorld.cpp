//
//  GameWorld.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Eddie Wu on 2/4/17.
//
//

#include "GameWorld.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

//Implementing createScene member function of class GameWorld
Scene* GameWorld::createScene() {
	auto scene = Scene::create();

	auto layer = GameWorld::create();

	scene->addChild(layer, 1, 999);

	return scene;
}

//Implementing init member function of class GameWorld
bool GameWorld::init() {
	//do the init job here

	if (!Layer::init())
	{
		return false;
	}

	auto character = Character::createCharacter("moveCharacter1.png");
	this->addChild(character, 1);
	
	setBackground();
	setCards();
	setMaster();


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

	return true;
}

//Implementing update member function of class GameWorld
void GameWorld::update(float delta) {
	//do the update job here

}

void GameWorld::setMaster() {
	gameMaster = GameMaster::createMaster();
	this->addChild(gameMaster);
}

void GameWorld::setCards() {
    
    auto card1 = Card::create("character1.png",9999,0);
    this->addChild(card1, 1);
    
    auto card2 = Card::create("character2.png", 998, 1);
    this->addChild(card2, 1);
    
    auto card3 = Card::create("arrow.png", 2, 2);
    this->addChild(card3, 1);
    
    auto card4 = Card::create("horse.png", 23, 3);
    this->addChild(card4, 1);
    
    auto card5 = Card::create("character1.png", 242, 4);
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
}
