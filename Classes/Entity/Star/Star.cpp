#include "Star.h"
#include <cocos2d.h>
using namespace cocos2d;
using namespace std;

Star* Star::create(int color)
{
	Star* ret = new Star;
	if (ret && ret->initWithFile(ret->getImage(color)))
	{
		ret->color = color;
		ret->selected = false;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

char* Star::getImage(int col)
{
	switch (col)
	{
	case STAR_COLOR::BLUE:
		return "blue.png";
	case STAR_COLOR::GREEN:
		return "green.png";
	case STAR_COLOR::PURPLE:
		return "purple.png";
	case STAR_COLOR::RED:
		return "red.png";
	case STAR_COLOR::YELLOW:
		return "orange.png";
	}
}

bool Star::isSelected()
{
	return selected;
}

int Star::getColor()
{
	return color;
}

void Star::setIndexIJ(int i, int j)
{
	index_i = i;
	index_j = j;
	/*Label* lb = Label::create("","Arial",20);
	string str = cocos2d::String::createWithFormat("%d",index_i)->_string + "-" + cocos2d::String::createWithFormat("%d",index_j)->_string;
	lb->setString(str);
	lb->setPosition(20,20);
	this->addChild(lb);*/
}

void Star::setDesPostion(const Point& p)
{
	desPostion = p;
}

void Star::updatePostion()
{
	if (desPostion.x != this->getPositionX())
	{
		this->setPositionX(this->getPositionX() - MOVE_SPEED);
		if (this->getPositionX() < desPostion.x)
		{
			this->setPositionX(desPostion.x);
		}
	}
	if (desPostion.y != this->getPositionY())
	{
		setPositionY(this->getPositionY() - MOVE_SPEED);
		if (this->getPositionY() < desPostion.y)
		{
			this->setPositionY(desPostion.y);
		}
	}
}