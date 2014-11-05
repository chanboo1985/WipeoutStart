#include "GameData.h"
#include <cocos2d.h>
USING_NS_CC;

GameData* GameData::_instance = nullptr;

GameData::GameData()
{
	this->init();
}

GameData* GameData::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameData;
	}
	return _instance;
}

void GameData::init()
{
	setCurLevel(0);
	setCurScore(0);
	setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));
}

void GameData::setCurLevel(int curlv)
{
	if(curlv < 0){return;}
	cur_levle = curlv;
	next_level = curlv + 1;
	next_score = getScoreByLevel(next_level);
}

int GameData::getScoreByLevel(int lv)
{
	int score = 0;
	if (lv == 1)
	{
		score = 1000;
	} 
	else if(lv == 2)
	{
		score = 3000;
	}
	else if(lv >= 3 && lv <= 10)
	{
		score = 3000 + 3000*(lv - 2);
	}else
	{
		score = 27000 + 4000*(lv - 10);
	}
	return score;
}

int GameData::getAwardScore(int size)
{
	static const int award[10][2] = 
	{
		{0, 2000},
		{1, 1980},
		{2, 1920},
		{3, 1820},
		{4, 1680},
		{5, 1500},
		{6, 1280},
		{7, 1020},
		{8, 720},
		{9, 380}
	};
	if (size > 9 || size < 0)
	{
		return 0;
	}
	return award[size][1];
}

void GameData::saveHistoryScore()
{
	UserDefault::getInstance()->setIntegerForKey("highestScore",getHistoryScore());
}
