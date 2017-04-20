//
//  MainMenuScene.cpp
//  TheWarOfThreeKingdoms
//
//  Created by Shun yin Ho  on 20/4/2017.
//
//

#include "MainMenuScene.h"
#include "GameWorld.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    
    //set menu item
    auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenu::Play, this));
    auto menu_item_2 = MenuItemFont::create("Quit", CC_CALLBACK_1(MainMenu::Quit, this));
    auto menu_item_3 = MenuItemFont::create("The Silent of the General", CC_CALLBACK_1(MainMenu::Play, this));
    
    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1));
    menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3));

    
    auto *menu = Menu::create(menu_item_3,menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    
    Sprite *background = Sprite::create("mainmenu.jpg");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    this->addChild(background, -1);
    background->setScaleX(visibleSize.width/ background->getContentSize().width);
    background->setScaleY(visibleSize.height/ background->getContentSize().height);
    
    
    return true;
}



void MainMenu::Play(cocos2d::Ref *pSender)
{
    CCLOG("Play");
    auto scene = GameWorld::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenu::Quit(cocos2d::Ref *pSender)
{
    CCLOG("Quit");
    Director::getInstance()->end();
}


void MainMenu::menuCloseCallback(Ref* pSender)
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
