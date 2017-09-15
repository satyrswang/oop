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
	//�����Ԫ��Ŀ�͸�
	int cardSize = (size.height - 36) / 4;
	//���Ƴ�4X4�ĵ�Ԫ��
	for (int i = 0; i < 4; i++)    	//�������
	{
		for (int j = 0; j < 4; j++)	//�������
		{
			//��Ҫ��Ļ�ֱ�������
			CardSprite *card = CardSprite::createCardSprite(0, cardSize, cardSize, cardSize*i + 80, cardSize*j + 20);
			cardArr[i][j] = card;
			addChild(card);     //��Ƭ����Ϊ�����һ��
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
	//������ָ��X��Y�ƶ��ľ���
	endX = beginX - endTouch.x;
	endY = beginY - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//���X���ƶ��ľ������Y�ᣬ���������ƶ�
		if (endX + 5 > 0)
		{
			//�����ƶ�
			OperationLeft();
			
			OperationCheck();createCardNumber();
			setScore();
		}
		else
		{
			//�����ƶ�
			OperationRight();
			
			OperationCheck();createCardNumber();
			setScore();
		}
	}
	else //�����������ƶ�
	{
		if (endY + 5 > 0)
		{
			//�����ƶ�
			OperationDown();
			
			OperationCheck();createCardNumber();
			setScore();
		}
		else
		{
			//�����ƶ�
			OperationUp();
			
			OperationCheck();createCardNumber();
			setScore();
		}
	}

}

bool HelloWorld::OperationLeft()
{
	CCLOG("left");

	//�ж���û�з����ƶ�
	bool isMove = false;
	//ÿһ�ж�ִ����ͬ���ڲ�ѭ����4��//
	for (int y = 0; y < 4; y++)    	//��
	{
		//ÿһ�е�������Ҫ��ǰ�е��ҵ�һ����Ϊ�յ��Ƶ�����������
		for (int x = 0; x < 4; x++)	//��
		{
			//�����forѭ���Ǵӵ�ǰ�������Ҳ�Ϊ�յģ����ǲ��п������Ʋ�����ע��break.�������в�Ϊ�յģ����Ȳ����������ˡ�
			for (int x1 = x + 1; x1<4; x1++)     //x1��x  ����һ����
			{
				if (cardArr[x1][y]->getNumber() > 0)    //��x1,y�����λ�ò�Ϊ��
				{
					if (cardArr[x][y]->getNumber() <= 0) //(x,y)λ��Ϊ�գ� ��x1,y��������Ҫ������
					{
						//������
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;     //����һ���£�����Ϊʲô�أ�ԭ��ܼ�ѽ���ոյ����ƺ󣬵�ǰ��Xλ�ô��������Ŷӵ�����һ���ˣ�����Ҫ������һ�����Ҫ��Ŀ���ǣ�����ӡ�  ������Ѱ�Ҳ�Ϊ�յĵ�һ��Ҫ������Ŷӵ�����һ���Ƚϣ�����������ͬ����ӡ�
						isMove = true;
					}
					//���� ������ͬ �������
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						score += cardArr[x][y]->getNumber();

						isMove = true;
					}
					// cardArr[x][y]->getNumber() ��= cardArr[x1][y]->getNumber()���ܶ�����ʲô��������
					break;    //���ε����ڲ�ѭ��������
				}
			}
		}
	}

	return isMove;

}
bool HelloWorld::OperationRight()
{
	CCLOG("right");
	//�ж���û�з����ƶ�
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

	//�ж���û�з����ƶ�
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

	//�ж���û�з����ƶ�
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
		//�����ƶ�
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		//�����ƶ�
		OperationDown();
	}
		break;
		//�����ƶ�
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		//�����ƶ�
		OperationLeft();
	}
		break;
		//�����ƶ�
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		//�����ƶ�
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
