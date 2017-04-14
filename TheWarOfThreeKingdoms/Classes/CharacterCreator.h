#pragma once
#include "Character.h"
#include <string>
using namespace std;
class CharacterCreator
{
public:
	

	Character* createCharacters(int charcterId, int direction);
	static CharacterCreator* getInstance();

private:
	CharacterCreator();
	const string characterFileName[7];

};

