#include "Card.h"



Card::Card()
{
}


Card::~Card()
{
}

Card* Card::create(const std::string& _file, int characterId, int position)
{
    Card* pCard = new Card();
    
    if (pCard->initWithSpriteFrameName(_file.c_str()))
    {
        pCard->autorelease();
        pCard->initOptions(position);
        pCard->setCharacterId(characterId);
        pCard->addEvents();
        
        return pCard;
    }
    
    CC_SAFE_DELETE(pCard);
    return NULL;
}

void Card::initOptions(int position)
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    this->setPosition(cocos2d::Vec2(visibleSize.width / 10+position*150, (visibleSize.height / 10)-50));
    this->setScale(0.50);
    // do things here like setTag(), setPosition(), any custom logic.
}


void Card::setCharacterId(int id)
{
    this->characterId = id;
}

int Card::getCharacterId()
{
    return this->characterId;
}

void Card::addEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        
        auto bounds = event->getCurrentTarget()->getBoundingBox();
        //auto target = static_cast<Card*>(event->getCurrentTarget());
        
        
        if (bounds.containsPoint(touch->getLocation())) {
            // the following code is for testing purpose
            std::stringstream touchDetails;
            touchDetails << "character id: " << this->getCharacterId();
            cocos2d::MessageBox(touchDetails.str().c_str(), "Touched");
            
            
            //pass character id to create suitable sprite here.
        }
        return true;
    };
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}
