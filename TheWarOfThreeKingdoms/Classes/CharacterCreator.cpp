#include "CharacterCreator.h"

using namespace std;

CharacterCreator::CharacterCreator()
{

}



Character*  CharacterCreator::charactersFactory(int charcterId,int direction){
//	string test = "moveCharacter1.png";
	string fileName[5] = { "moveCharacter2.png", "moveCharacter3.png", "moveCharacter4.png", "moveCharacter5.png", "moveCharacter6.png"};
	return Character::createCharacter(fileName[charcterId].c_str(), direction);
}

CharacterCreator* CharacterCreator::getInstance()
{
	static CharacterCreator *pInst;
	return pInst;
}