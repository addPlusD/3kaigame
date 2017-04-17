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

int castle = 100,enemyCastle = 100;

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

	/*auto character = Character::createCharacter("moveCharacter1.png");
	this->addChild(character, 1);*/
	
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
    setHP();
}

void GameWorld::setMaster() {
	gameMaster = GameMaster::createMaster();
	this->addChild(gameMaster);
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
    
    auto card5 = Card::create("character1.png", 4, 4);
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
    
    auto castleHP = Sprite::create("HP_bar.png");
    castleHP->setTextureRect(Rect(0, 0, 308, 47));
    castleHP->setScale(0.3);
    castleHP->setPosition(Vec2(origin.x + visibleSize.width - castle->getContentSize().width / 2+5,
                               origin.y + visibleSize.height / 2 + castle->getContentSize().height / 2+40));
    castleHP->setTag(100);
    this->addChild(castleHP, 1);
    
    auto enemyCastleHP = Sprite::create("HP_bar.png");
    enemyCastleHP->setTextureRect(Rect(0, 0, 308, 47));
    enemyCastleHP->setScale(0.3);
    enemyCastleHP->setPosition(Vec2(origin.x + enemyCastle->getContentSize().width / 2+5,
                                    origin.y + visibleSize.height / 2 + enemyCastle->getContentSize().height / 2 +40));
    enemyCastleHP->setTag(101);
    this->addChild(enemyCastleHP, 1);
    
}

void GameWorld::setHP() {
    auto* castleHP = (Sprite*)getChildByTag(100);
    castleHP->setTexture("HP_bar.png");
    castleHP->setTextureRect(getHPRect(castle));
    
    auto* enemyCastleHP = (Sprite*)getChildByTag(101);
    enemyCastleHP->setTexture("HP_bar.png");
    enemyCastleHP->setTextureRect(getHPRect(enemyCastle));
}

Rect GameWorld::getHPRect(int hp){
    switch ((int)round(hp/4)){
        case 25:
            return Rect(0, 0, 312, 52);
            break;
        case 24:
            return Rect(624, 0, 312, 52);
            break;
        case 23:
            return Rect(312, 52, 312, 52);
            break;
        case 22:
            return Rect(0, 104, 312, 52);
            break;
        case 21:
            return Rect(624, 104, 312, 52);
            break;
        case 20:
            return Rect(312, 156, 312, 52);
            break;
        case 19:
            return Rect(0, 208, 312, 52);
            break;
        case 18:
            return Rect(624, 208, 312, 52);
            break;
        case 17:
            return Rect(312, 260, 312, 52);
            break;
        case 16:
            return Rect(0, 312, 312, 52);
            break;
        case 15:
            return Rect(624, 312, 312, 52);
            break;
        case 14:
            return Rect(312, 364, 312, 52);
            break;
        case 13:
            return Rect(0, 416, 312, 52);
            break;
        case 12:
            return Rect(624, 416, 312, 52);
            break;
        case 11:
            return Rect(312, 468, 312, 52);
            break;
        case 10:
            return Rect(0, 520, 312, 52);
            break;
        case 9:
            return Rect(624, 520, 312, 52);
            break;
        case 8:
            return Rect(312, 572, 312, 52);
            break;
        case 7:
            return Rect(0, 624, 312, 52);
            break;
        case 6:
            return Rect(624, 624, 312, 52);
            break;
        case 5:
            return Rect(312, 676, 312, 52);
            break;
        case 4:
            return Rect(0, 728, 312, 52);
            break;
        case 3:
            return Rect(624, 780, 312, 52);
            break;
        case 2:
            return Rect(312, 780, 312, 52);
            break;
        case 1:
            return Rect(0, 832, 312, 52);
            break;
        case 0:
            return Rect(312, 832, 312, 52);
            break;
        default:
            return Rect(0, 0, 312, 52);
            break;
    }
}

