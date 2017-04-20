//
//  MainMenuScene.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 20/4/2017.
//
//
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "GameWorld.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PauseScene::create();
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto menu_item_1 = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseScene::Resume, this));
    auto menu_item_2 = MenuItemFont::create("Return Main Menu", CC_CALLBACK_1(PauseScene::MainMenu, this));
    
    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    
    auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    
    return true;
}

void PauseScene::Resume(cocos2d::Ref *pSender)
{
    CCLOG("Resume");
    auto scene = Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(scene);
}

void PauseScene::MainMenu(cocos2d::Ref *pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->pushScene(scene);
    CCLOG("MainMenu");
}


void PauseScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
