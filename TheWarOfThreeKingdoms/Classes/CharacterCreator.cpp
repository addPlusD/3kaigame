#include "CharacterCreator.h"
USING_NS_CC;
using namespace std;

CharacterCreator::CharacterCreator()
{

}



Character*  CharacterCreator::charactersFactory(int charcterId,int direction){
//	string test = "moveCharacter1.png";
	string fileName[5] = { "moveCharacter2.png", "moveCharacter3.png", "moveCharacter4.png", "moveCharacter5.png", "moveCharacter6.png"};
	auto newCharacter = Character::createCharacter(fileName[charcterId].c_str(), direction);
    int HP;
	switch (charcterId) {
		case 0:
			newCharacter->setProperty(500,50,20,1);// int health, int attackDamage, int attackRange, float speed
            HP = 500;
		break;

		case 1:
			newCharacter->setProperty(400, 40, 30, 2);
            HP = 400;
		break;

		case 2:
			newCharacter->setProperty(300, 30, 40, 3);
            HP = 300;
		break;

		case 3:
			newCharacter->setProperty(200, 20, 50, 4);
            HP = 200;
        break;

		case 4:
			newCharacter->setProperty(100, 10, 60, 5);
            HP = 100;
		break;
	}
	
    auto HPBar = Bar::create(HP);
    HPBar->setScale(0.1);
    HPBar->setTag(101);
    HPBar->setPosition(Vec2(newCharacter->getContentSize().width/2,30));
    newCharacter->addChild(HPBar, 1);
	
	return newCharacter;
}

CharacterCreator* CharacterCreator::getInstance()
{
	static CharacterCreator *pInst;
	return pInst;
}
