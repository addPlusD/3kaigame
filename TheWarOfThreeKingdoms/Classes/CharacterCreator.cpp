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
//    int HP;
	switch (charcterId) {
		case 0:
			newCharacter->setProperty(500,70,20,1, 4);
            // int health, int attackDamage(+20), int attackRange, float speed, float cooldown
            newCharacter->setName("Player1");
//            HP = 500;
		break;

		case 1:
            newCharacter->setProperty(400, 40, 30, 2, 3);
            newCharacter->setName("Player2");
//            HP = 400;
		break;

		case 2:
            newCharacter->setProperty(300, 30, 40, 3, 2);
            newCharacter->setName("Player3");
//            HP = 300;
		break;

		case 3:
            newCharacter->setProperty(200, 20, 50, 4, 2);
            newCharacter->setName("Player4");
			break;
//            HP = 200;
        break;

		case 4:
            newCharacter->setProperty(100, 10, 60, 5, 1);
            newCharacter->setName("Player5");
//            HP = 100;
		break;
	}
	
//    auto HPBar = Bar::create(HP);
//    HPBar->setScale(0.1);
//    HPBar->setTag(101);
//    HPBar->setPosition(Vec2(newCharacter->getContentSize().width/2,30));
//    newCharacter->addChild(HPBar, 1);
	
	return newCharacter;
}

CharacterCreator* CharacterCreator::getInstance()
{
	static CharacterCreator *pInst;
	return pInst;
}
