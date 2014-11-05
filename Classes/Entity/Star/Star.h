#ifndef __STAR_H__
#define __STAR_H__
#include <cocos2d.h>
USING_NS_CC;
//Star����ǵ������ǵİ�װ����Ҫ�������ǵ���ɫ�����ǵĵ�ǰλ�ã�
//���ǵ�Ŀ��λ�ã�Ϊʲô����������λ�ã��������˵�����Լ������ھ����е�λ�ã������Ǿ�����أ�
class Star : public Sprite
{
public:
	enum STAR_COLOR
	{
		GREEN,
		RED,
		YELLOW,
		PURPLE,
		BLUE
	};
	
	static Star* create(int col);

	bool isSelected();

	inline void setSelected(bool b){selected = b;}

	int getColor();

	void setDesPostion(const Point& p);

	inline Point getDesPostion(){return desPostion;}

	void updatePostion();

	inline int getIndexI(){return index_i;}

	inline int getIndexJ(){return index_j;}

	void setIndexIJ(int i, int j);
public:
	static const int MOVE_SPEED = 4;
	static const int COLOR_MAX_NUM = 5;
	static const int STAR_WIDTH = 48;
	static const int STAR_HEIGHT = 48;
private:
	char* getImage(int col);
private:
	int color;
	Point desPostion;
	bool selected;
	int index_i;
	int index_j;
};

#endif