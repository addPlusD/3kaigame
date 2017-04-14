#include "CharacterCreator.h"



CharacterCreator::CharacterCreator()
{
	string characterFileName[] = { "moveCharacter1.png", " ", " ", " ", " ", " ", " " };
}



Character*  CharacterCreator::createCharacters(int charcterId,int direction){
	return Character::createCharacter(characterFileName[charcterId], direction);
}

CharacterCreator* CharacterCreator::getInstance()
{
	static CharacterCreator *pInst;
	return pInst;
}