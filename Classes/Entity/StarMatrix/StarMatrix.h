#ifndef __STAR_MATRIX_H__
#define __STAR_MATRIX_H__
#include <cocos2d.h>
#include <deque>
#include "Layer/GameLayer.h"
#include "Entity/Star/Star.h"
using namespace cocos2d;
using namespace std;
class GameLayer;
class StarMatrix : public Node
{
public:
	static StarMatrix* create(GameLayer* layer);

	virtual bool init(GameLayer* layer);

	void updateStar(float delta);

	void onTouch(const Point& p);

	void setNeedClear(bool b);

	void initMatrix();
private:
	Point getPostionByIndex(int i, int j);

	Star* getStarByTouch(const Point& p);

	void getSelectedList(Star* s);

	void deleteSelectedList();

	void adjustMatrix();

	void refreshScore();

	bool isEnded();

	void clearMatrixOneByOne();

	int getLeftStarNum();
public:
	const static int ROW_NUM = 10;
	const static int COL_NUM = 10;
private:
	Star* stars[ROW_NUM][COL_NUM];
	deque<Star*> selectedList;
	bool needClear;
	static float ONE_CLEAR_TIME;
	GameLayer* m_layer;
	float clearSumTime;
};

#endif