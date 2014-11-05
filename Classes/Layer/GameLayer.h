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

	void floatLevelText();//Ʈ���ؿ���Ϣ

	void floatTargetScoreText();//Ʈ��Ŀ�����

	void removeFloatText();//�Ƴ��ؿ���Ϣ�Լ�Ŀ�����

	void showStarMatrix();//�������Ǿ���

	virtual void update(float delay);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);//���ܴ����¼�

	void refreshTopMenu();//ˢ�¶�����Ϣ

	void showLinkNum(int size);//��ʾ������Ϣ

	void hideLinkNum();//����������Ϣ

	void floatLeftStarMsg(int leftNum);//��ʾʣ�µ���������

	void gotoNextLevel();//������һ��

	void gotoGameOver();//��Ϸ����
private:
	FloatText* _levelMsg;//�ؿ���Ϣ

	FloatText* _targetScore;//Ŀ�����

	TopMenu* topMenu;//������Ϣ

	StarMatrix* matrix;//��������

	Label* linkNum;//������Ϣ
};

#endif