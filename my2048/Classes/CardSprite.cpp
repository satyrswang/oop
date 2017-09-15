#include "CardSprite.h"


CardSprite::CardSprite()
{
}


CardSprite::~CardSprite()
{
}


CardSprite * CardSprite::createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	CardSprite * enemy = new CardSprite();

	if (enemy && enemy->init())
	{
		enemy->autorelease();

		enemy->enemyInit(number, wight, height, CardSpriteX, CardSpriteY);
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return enemy;
}

bool CardSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void CardSprite::enemyInit(int number, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	//初始化数字
	this->number = number;
	//加入卡片背景颜色
	colorBackground = LayerColor::create(Color4B(200, 190, 180, 255), wight - 15, height - 15);     //默认的颜色和大小
	colorBackground->setPosition(Point(CardSpriteX, CardSpriteY));     //位置

	//判断如果大于0就显示，否则就不显示
	if (number > 0)
	{
		//加入字体
		labelCardNumber = LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "Consolas", 100);    //标签的内容\格式
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width / 2, colorBackground->getContentSize().height / 2));   //标签的位置
		labelCardNumber->setTag(8);     //id标识
		colorBackground->addChild(labelCardNumber);    //标签作为背景的下一级
	}
	else    //默认的
	{
		//加入字体
		labelCardNumber = LabelTTF::create("", "Consolas", 100);
		labelCardNumber->setPosition(Point(colorBackground->getContentSize().width / 2, colorBackground->getContentSize().height / 2));
		labelCardNumber->setTag(8);
		colorBackground->addChild(labelCardNumber);
	}
	this->addChild(colorBackground);    //背景作为卡片的下一级

}

int CardSprite::getNumber()
{
	return number;
}
void CardSprite::setNumber(int num)
{
	number = num;
	if (num > 0)
	{
		labelCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else
	{
		labelCardNumber->setString("");
	}


	if (num >= 0)
	{
		labelCardNumber->setFontSize(100);
	}
	if (num >= 16)
	{
		labelCardNumber->setFontSize(90);
	}
	if (num >= 128)
	{
		labelCardNumber->setFontSize(60);
	}
	if (num >= 1024)
	{
		labelCardNumber->setFontSize(40);
	}


	if (number == 0)
	{
		colorBackground->setColor(Color3B(200, 190, 180));
	}
	if (number == 2)
	{
		colorBackground->setColor(Color3B(240, 230, 220));
	}
	if (number == 4)
	{
		colorBackground->setColor(Color3B(240, 220, 200));
	}
	if (number == 8) {
		colorBackground->setColor(Color3B(240, 180, 120));
	}
	if (number == 16) {
		colorBackground->setColor(Color3B(240, 140, 90));
	}
	if (number == 32) {
		colorBackground->setColor(Color3B(240, 120, 90));
	}
	if (number == 64) {
		colorBackground->setColor(Color3B(240, 90, 60));
	}
	if (number == 128) {
		colorBackground->setColor(Color3B(240, 90, 60));
	}
	if (number == 256) {
		colorBackground->setColor(Color3B(240, 200, 70));
	}
	if (number == 512) {
		colorBackground->setColor(Color3B(240, 200, 70));
	}
	if (number == 1024) {
		colorBackground->setColor(Color3B(0, 130, 0));
	}
	if (number == 2048) {
		colorBackground->setColor(Color3B(0, 130, 0));
	}


}