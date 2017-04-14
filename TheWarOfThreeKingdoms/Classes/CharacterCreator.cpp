#include "CharacterCreator.h"



CharacterCreator::CharacterCreator()
{
	string characterFileName[] = { "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png", 
		"moveCharacter1.png", "moveCharacter1.png" };
}



Character*  CharacterCreator::createCharacters(int charcterId,int direction){
	return Character::createCharacter("moveCharacter1.png", direction);
}

CharacterCreator* CharacterCreator::getInstance()
{
	static CharacterCreator *pInst;
	return pInst;
}