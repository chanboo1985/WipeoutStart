#include "StarMatrix.h"
#include "../Effect/StarParticle.h"
#include "../Effect/ComboEffect.h"
#include "Util/GameData/GameData.h"
#include <ctime>
float StarMatrix::ONE_CLEAR_TIME = 0.05f;
StarMatrix* StarMatrix::create(GameLayer* layer)
{
	StarMatrix* matrix = new StarMatrix;
	if (matrix && matrix->init(layer))
	{
		matrix->autorelease();
		return matrix;
	}
	CC_SAFE_DELETE(matrix);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer)
{
	if (!Node::init())
	{
		return false;
	}
	m_layer = layer;
	needClear = false;
	clearSumTime = 0;
	memset(stars,0,sizeof(Star*)*ROW_NUM*COL_NUM);
	initMatrix();
	return true;
}

void StarMatrix::initMatrix()
{
	srand(time(0));
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			int color = abs(rand()%Star::COLOR_MAX_NUM);
			Star* star = Star::create(color);
			stars[i][j] = star;
			star->setPosition(getPostionByIndex(i,j) + Point(0,200));
			star->setDesPostion(getPostionByIndex(i,j));
			star->setIndexIJ(i,j);
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPostionByIndex(int i, int j)
{
	float x = j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y = (StarMatrix::COL_NUM - i)*Star::STAR_HEIGHT - Star::STAR_HEIGHT/2;
	return Point(x,y);
}

void StarMatrix::updateStar(float delta)
{
	for(int i = 0;i < ROW_NUM;i++){
		for(int j = 0;j< COL_NUM;j++){
			if(stars[i][j]!=nullptr){
				stars[i][j]->updatePostion();
			}
		}
	}
	if(needClear){
		clearSumTime += delta;
		if(clearSumTime > ONE_CLEAR_TIME){
			clearMatrixOneByOne();
			clearSumTime = 0;
		}
	}
}

void StarMatrix::clearMatrixOneByOne()
{
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			showStarParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}
	//�ܹ�ִ�е���һ��˵��MatrixȫΪ�գ�������Ҫ���
	needClear = false;
	//ת����һ�ػ��ߵ���������Ϸ�Ĵ���
	if(GameData::getInstance()->getCurScore() >= GameData::getInstance()->getNextScore()){
		GameData::getInstance()->setCurLevel(GameData::getInstance()->getCurLevel() + 1);
		m_layer->gotoNextLevel();
	}else{
		m_layer->gotoGameOver();
		CCLOG("GAME OVER");
	}
}

void StarMatrix::onTouch(const Point& p)
{
	Star* star = getStarByTouch(p);
	if (star)
	{
		getSelectedList(star);
		CCLOG("SIZE = %d",selectedList.size());
		deleteSelectedList();
	}
}

Star* StarMatrix::getStarByTouch(const Point& p){
	int k = p.y/Star::STAR_HEIGHT;//����Ҫ��Kתһ��int ��Ȼ�ò�����ȷ���
	int i = ROW_NUM - 1 - k;
	int j = p.x/Star::STAR_WIDTH;
	if(i >= 0 && i < ROW_NUM && 
		j >= 0 && j < COL_NUM &&
		stars[i][j] != nullptr){
			CCLOG("i=%d,j=%d",i,j);
			return stars[i][j];
	}else{
		return nullptr;
	}
}

void StarMatrix::getSelectedList(Star* s){
	selectedList.clear();
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for(it= travelList.begin();it != travelList.end();){
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//��
		if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i-1][index_j]);
		}
		//��
		if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i+1][index_j]);
		}
		//��
		if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j-1]);
		}
		//��
		if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j+1]);
		}
		if(!star->isSelected()){
			star->setSelected(true);
			selectedList.push_back(star);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
}

void StarMatrix::deleteSelectedList()
{
	if (selectedList.size() <= 1)
	{
		m_layer->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return;
	}
	for (auto it = selectedList.begin();it != selectedList.end();it++)
	{
		Star* star = *it;
		//����Ч��
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
	}
	//��ըЧ��
	showComboEffect(selectedList.size(),this);
	//ˢ�·���
	refreshScore();
	//��ʾ��������
	m_layer->showLinkNum(selectedList.size());
	adjustMatrix();
	if (isEnded())
	{
		m_layer->floatLeftStarMsg(getLeftStarNum());
		CCLOG("ENDED");
	}
}

int StarMatrix::getLeftStarNum()
{
	int ret = 0;
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (stars[i][j] == nullptr)
			{
				continue;
			}
			ret++;
		}
	}
	return ret;
}

bool StarMatrix::isEnded()
{
	for (int i = 0; i < ROW_NUM; i++)
	{
		for (int j = 0; j < COL_NUM; j++)
		{
			if (stars[i][j] == nullptr)
			{
				continue;
			}
			int curColor = stars[i][j]->getColor();
			//����һ���Ƿ�����ͬ��ɫ������
			if (i-1 >= 0 && stars[i-1][j] != nullptr && stars[i-1][j]->getColor() == curColor)
			{
				return false;
			}
			//����һ���Ƿ�����ͬ��ɫ������
			if (i+1 < ROW_NUM && stars[i+1][j] != nullptr && stars[i+1][j]->getColor() == curColor)
			{
				return false;
			}
			//���һ���Ƿ�����ͬ��ɫ������
			if (j-1 >= 0 && stars[i][j-1] != nullptr && stars[i][j-1]->getColor() == curColor)
			{
				return false;
			}
			//�Ҳ�һ���Ƿ�����ͬ��ɫ������
			if (j+1 < COL_NUM && stars[i][j+1] != nullptr && stars[i][j+1]->getColor() == curColor)
			{
				return false;
			}
		}
	}
	return true;
}

void StarMatrix::refreshScore()
{
	GameData *data = GameData::getInstance();
	data->setCurScore(data->getCurScore() + selectedList.size()*selectedList.size()*5);
	if (data->getCurScore() > data->getHistoryScore())
	{
		data->setHistoryScore(data->getCurScore());
	}
	m_layer->refreshTopMenu();
}

//��������Ǻ��������λ��
void StarMatrix::adjustMatrix()
{
	//��ֱ�������
	for (int i = ROW_NUM - 1; i >= 0; i--)
	{
		for (int j = COL_NUM - 1; j >= 0; j--)
		{
			if (stars[i][j] == nullptr)
			{
				int top = i;
				int nullNum = 0;//��ֱ�����м�����λ
				while (stars[top][j] == nullptr)
				{
					nullNum++;
					top--;
					if (top < 0)
					{
						break;
					}
				}
				for (int begin_i = i - nullNum; begin_i >= 0; begin_i--)
				{
					if (stars[begin_i][j] == nullptr)
					{
						continue;
					}
					Star* star = stars[begin_i + nullNum][j] = stars[begin_i][j];
					star->setIndexIJ(begin_i + nullNum,j);
					star->setDesPostion(getPostionByIndex(begin_i + nullNum,j));
					stars[begin_i][j] = nullptr;
				}
			}else
			{
				continue;
			}
		}
	}
	//ˮƽ�������:���ڴ�ֱ��������Ƕ��������ƶ����������ֻ���ж�ÿһ�е����һ���Ƿ�Ϊ��
	for (int j = 0; j < COL_NUM; j++)
	{
		if (stars[ROW_NUM - 1][j] == nullptr)
		{
			int pos = j;
			int nullNum = 0;
			while (stars[ROW_NUM-1][pos] == nullptr)
			{
				pos++;
				nullNum++;
			}
			for (int begin_i = 0; begin_i < ROW_NUM; begin_i++)
			{
				for (int begin_j = j + nullNum; begin_j < COL_NUM; begin_j++)
				{
					if (stars[begin_i][begin_j] == nullptr)
					{
						continue;
					}
					Star* star = stars[begin_i][begin_j-nullNum] = stars[begin_i][begin_j];
					star->setIndexIJ(begin_i,begin_j-nullNum);
					star->setDesPostion(getPostionByIndex(begin_i,begin_j-nullNum));
					stars[begin_i][begin_j] = nullptr;
				}
			}
		}
	}
}

void StarMatrix::setNeedClear(bool b)
{
	needClear = b;
}