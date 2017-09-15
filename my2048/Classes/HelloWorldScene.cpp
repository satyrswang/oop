#include "HelloWorldScene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	auto layerColorBG = LayerColor::create(Color4B(100,90,100,255));
	this->addChild(layerColorBG);

	createCardSprite(visibleSize);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	auto cardNumberTitle = LabelTTF::create("Score", "Consolas", 80);
	cardNumberTitle->setPosition(Point(visibleSize.width / 2 + 340, visibleSize.height / 2 + 130));
	addChild(cardNumberTitle);

	score = 0;
	cardNumberTTF = LabelTTF::create("0", "Consolas", 70);
	cardNumberTTF->setPosition(Point(visibleSize.width / 2 + 340, visibleSize.height / 2 - 100));
	addChild(cardNumberTTF);

	createCardNumber();
	createCardNumber();
    return true;
}
void HelloWorld::setScore()
{
	cardNumberTTF->setString(__String::createWithFormat("%i", score)->getCString());
}

void HelloWorld::OperationCheck()
{
	bool isGameOver = true;
	for (int  y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[y][x]->getNumber() == 0 ||
				(x<3 && cardArr[x][y]->getNumber()== cardArr[x+1][y]-> getNumber())  ||
				(x>0 && cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())||
				(y<3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber())||
				(y>0 && cardArr[x][y]->getNumber() == cardArr[x][y -1]->getNumber()))
			{
				isGameOver = false;
			}
		}

	}
	if (isGameOver)
	{
		log("GameOver!!!!!!");

		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}
}

void HelloWorld::createCardSprite(Size size)
{
	//求出单元格的宽和高
	int cardSize = (size.height - 36) / 4;
	//绘制出4X4的单元格
	for (int i = 0; i < 4; i++)    	//数组的列
	{
		for (int j = 0; j < 4; j++)	//数组的行
		{
			//需要屏幕分辨率适配
			CardSprite *card = CardSprite::createCardSprite(0, cardSize, cardSize, cardSize*i + 80, cardSize*j + 20);
			cardArr[i][j] = card;
			addChild(card);     //卡片是作为层的下一级
		}
	}

}

void HelloWorld::createCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	if (cardArr[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}

}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point beginTouch = touch->getLocation();
	beginX = beginTouch.x;
	beginY = beginTouch.y;
		return true;
}
void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point endTouch = touch->getLocation();
	//计算手指在X，Y移动的距离
	endX = beginX - endTouch.x;
	endY = beginY - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//如果X轴移动的距离大于Y轴，则是左右移动
		if (endX + 5 > 0)
		{
			//向左移动
			OperationLeft();
			
			OperationCheck();createCardNumber();
			setScore();
		}
		else
		{
			//向右移动
			OperationRight();
			
			OperationCheck();createCardNumber();
			setScore();
		}
	}
	else //否则是上下移动
	{
		if (endY + 5 > 0)
		{
			//向下移动
			OperationDown();
			
			OperationCheck();createCardNumber();
			setScore();
		}
		else
		{
			//向上移动
			OperationUp();
			
			OperationCheck();createCardNumber();
			setScore();
		}
	}

}

bool HelloWorld::OperationLeft()
{
	CCLOG("left");

	//判断有没有发生移动
	bool isMove = false;
	//每一行都执行相同的内层循环。4行//
	for (int y = 0; y < 4; y++)    	//行
	{
		//每一列的作用是要当前列的右第一个不为空的移到最紧随着左边
		for (int x = 0; x < 4; x++)	//列
		{
			//下面的for循环是从当前列向右找不为空的，我们才有可能左移操作。注意break.决定了有不为空的，就先不在往后找了。
			for (int x1 = x + 1; x1<4; x1++)     //x1是x  的右一个。
			{
				if (cardArr[x1][y]->getNumber() > 0)    //（x1,y）这个位置不为空
				{
					if (cardArr[x][y]->getNumber() <= 0) //(x,y)位置为空， （x1,y）的内容要左移了
					{
						//左移了
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;     //在来一边呗，这是为什么呢？原因很简单呀，刚刚的左移后，当前的X位置存的是最靠左排队的最右一个了，我们要重新走一遍的主要的目的是，“相加”  在右面寻找不为空的第一个要与最靠左排队的最右一个比较，两个数字相同就相加。
						isMove = true;
					}
					//两个 数字相同 ，相加呗
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						score += cardArr[x][y]->getNumber();

						isMove = true;
					}
					// cardArr[x][y]->getNumber() ！= cardArr[x1][y]->getNumber()不能动，就什么都不做呗
					break;    //本次的最内层循环结束了
				}
			}
		}
	}

	return isMove;

}
bool HelloWorld::OperationRight()
{
	CCLOG("right");
	//判断有没有发生移动
	bool isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;

}
bool HelloWorld::OperationDown()
{
	CCLOG("down");

	//判断有没有发生移动
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y <4; y++)
		{
			for (int y1 = y + 1; y1<4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;



	return true;
}
bool HelloWorld::OperationUp()
{
	CCLOG("up");

	//判断有没有发生移动
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;

}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		OperationUp();
	}
		break;
		//向下移动
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		//向下移动
		OperationDown();
	}
		break;
		//向左移动
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		//向左移动
		OperationLeft();
	}
		break;
		//向右移动
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		//向左移动
		OperationRight();
	}
		break;

	default:
		break;
	}
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
