#include "GameLayer.h"
#include "Util/GameData/GameData.h"
#include "Util/zhCN/zhCN.h"
#include "Scene/MenuScene.h"
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	matrix = nullptr;
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	topMenu = TopMenu::create();
	this->addChild(topMenu);
	linkNum = Label::create("","Arial",40);
	linkNum->setPosition(visibleSize.width/2,visibleSize.height-250);
	linkNum->setVisible(false);
	this->addChild(linkNum,1);
	floatLevelText();
	return true;
}

void GameLayer::floatLevelText()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_levelMsg = FloatText::create(parseStr("guanqia") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextLevel())->_string,50,ccp(visibleSize.width,visibleSize.height/3*2));
	this->addChild(_levelMsg,1);
	_levelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::floatTargetScoreText,this));
}

void GameLayer::floatTargetScoreText()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_targetScore = FloatText::create(parseStr("mubiao") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextScore())->_string,50,ccp(visibleSize.width,visibleSize.height/3));
	this->addChild(_targetScore,1);
	_targetScore->floatIn(1.0f,CC_CALLBACK_0(GameLayer::removeFloatText,this));
}

void GameLayer::removeFloatText()
{
	_levelMsg->floatOut(0.5f,nullptr);
	_targetScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

void GameLayer::showStarMatrix()
{
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
}

void GameLayer::update(float delay)
{
	if (matrix)
	{
		matrix->updateStar(delay);
	}
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point p = touch->getLocationInView();
	p = Director::getInstance()->convertToGL(p);
	CCLOG("x=%f y=%f",p.x,p.y);
	if (matrix)
	{
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshTopMenu()
{
	topMenu->refresh();
}

void GameLayer::showLinkNum(int size)
{
	string s = String::createWithFormat("%d",size)->_string + parseStr("lianji") + 
		String::createWithFormat("%d",size*size*5)->_string + parseStr("fen");
	linkNum->setString(s);
	linkNum->setVisible(true);
}

void GameLayer::hideLinkNum()
{
	linkNum->setVisible(false);
}

void GameLayer::floatLeftStarMsg(int leftNum)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatText* leftStarMsg1 = FloatText::create(parseStr("shengyu") + String::createWithFormat("%d",leftNum)->_string +parseStr("ge"), 
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
	int jiangLiScore = GameData::getInstance()->getAwardScore(leftNum);
	FloatText* leftStarMsg2 = FloatText::create(parseStr("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + parseStr("fen"),
		50,Point(visibleSize.width,visibleSize.height/2 - 50));
	this->addChild(leftStarMsg2);
	leftStarMsg1->floatInOut(0.5f,1.0f,[=](){
		hideLinkNum();
		matrix->setNeedClear(true);
		GameData* data = GameData::getInstance();
		data->setCurScore(data->getCurScore() + jiangLiScore);
		if (data->getCurScore() > data->getHistoryScore())
		{
			data->setHistoryScore(data->getCurScore());
		}
		refreshTopMenu();
	});
	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
}

void GameLayer::gotoNextLevel()
{
	refreshTopMenu();
	floatLevelText();
}

void GameLayer::gotoGameOver()
{
	GameData::getInstance()->saveHistoryScore();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatText* gameOver = FloatText::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOver);
	gameOver->floatIn(1.0f,[]{Director::getInstance()->replaceScene(MenuScene::create());});
}