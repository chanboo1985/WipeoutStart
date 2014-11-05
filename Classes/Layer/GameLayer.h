#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "Entity/FloatText/FloatText.h"
#include "Entity/TopMenu/TopMenu.h"
#include "Entity/StarMatrix/StarMatrix.h"
USING_NS_CC;
class StarMatrix;
class GameLayer : public Layer
{
public:
	GameLayer(){}

	~GameLayer(){}

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void floatLevelText();//飘出关卡信息

	void floatTargetScoreText();//飘出目标分数

	void removeFloatText();//移除关卡信息以及目标分数

	void showStarMatrix();//创建星星矩阵

	virtual void update(float delay);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);//接受触摸事件

	void refreshTopMenu();//刷新顶部信息

	void showLinkNum(int size);//显示连击信息

	void hideLinkNum();//隐藏连击信息

	void floatLeftStarMsg(int leftNum);//显示剩下的星星数量

	void gotoNextLevel();//跳到下一关

	void gotoGameOver();//游戏结束
private:
	FloatText* _levelMsg;//关卡信息

	FloatText* _targetScore;//目标分数

	TopMenu* topMenu;//顶部信息

	StarMatrix* matrix;//所有星星

	Label* linkNum;//连击信息
};

#endif