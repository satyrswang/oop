#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "CardSprite.h"
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void OperationCheck();
private:
	void createCardSprite(Size size);
	void createCardNumber();

	bool OperationLeft();
	bool OperationRight();
	bool OperationDown();
	bool OperationUp();

	int score;
	void setScore();

	LabelTTF * cardNumberTTF;

	CardSprite * cardArr[4][4];
	int beginX, beginY, endX, endY;
};

#endif // __HELLOWORLD_SCENE_H__
