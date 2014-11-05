#include "TopMenu.h"
#include "Util/GameData/GameData.h"
#include "Util/zhCN/zhCN.h"
bool TopMenu::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	highestScore = Label::create(parseStr("highestScore") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getHistoryScore())->_string,"Verdana-Bold",30);
	highestScore->setPosition(visibleSize.width/2,visibleSize.height - 50);
	this->addChild(highestScore);

	level = Label::create(parseStr("guanqia") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextLevel())->_string,"Verdana-Bold",30);
	level->setPosition(200,visibleSize.height - 100);
	this->addChild(level);

	targetScore = Label::create(parseStr("mubiao") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextScore())->_string,"Verdana-Bold",30);
	targetScore->setPosition(400,visibleSize.height - 100);
	this->addChild(targetScore);

	curScore = Label::create(cocos2d::String::createWithFormat("%d",GameData::getInstance()->getCurScore())->_string,"Verdana-Bold",30);
	curScore->setPosition(visibleSize.width/2,visibleSize.height - 150);
	this->addChild(curScore);
	return true;
}

void TopMenu::refresh()
{
	char buff[64];
	sprintf(buff,"%d",GameData::getInstance()->getCurScore());
	curScore->setString(buff);

	string history = parseStr("highestScore") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getHistoryScore())->_string;
	highestScore->setString(history);

	string guanqia = parseStr("guanqia") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextLevel())->_string;
	level->setString(guanqia);

	string target = parseStr("mubiao") + cocos2d::String::createWithFormat("%d",GameData::getInstance()->getNextScore())->_string + parseStr("fen");
	targetScore->setString(target);
}