#pragma once
#include "Character.h"
#include "Bar.h"
#include <string>
using namespace std;
class CharacterCreator
{


public:
	Character* charactersFactory(int charcterId, int direction);
	static CharacterCreator* getInstance();

private:
	CharacterCreator();
	/*string fileName[7] = { "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png", "moveCharacter1.png",
		"moveCharacter1.png", "moveCharacter1.png"};*/

};

