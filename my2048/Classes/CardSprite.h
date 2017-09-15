#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CardSprite :
	public Sprite
{
public:
	CardSprite();
	~CardSprite();

	static CardSprite * createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	virtual bool init();
	void enemyInit(int number, int wight, int height, float CardSpriteX, float CardSpriteY);

public :
	int getNumber();
	void setNumber(int num);
private:
	int number;

	LabelTTF * labelCardNumber;

	LayerColor * colorBackground;

};

