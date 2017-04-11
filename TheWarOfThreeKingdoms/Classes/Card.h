#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <stdio.h>
#include "cocos2d.h"
#include <string>


class Card:public cocos2d::Sprite
{
public:
	Card();
	~Card();

	static Card* create(const std::string& _file, int characterId, int position);

	void initOptions(int position);

	void addEvents();
	void setCharacterId(int id);
	int getCharacterId();
//	void touchEvent(cocos2d::Touch* touch, cocos2d::Vector2 _p);

private:
	int characterId;
};
#endif // _CARD_HPP_

