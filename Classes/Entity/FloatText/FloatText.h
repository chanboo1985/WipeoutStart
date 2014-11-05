#ifndef __FLOAT_TEXT_H__
#define __FLOAT_TEXT_H__
#include <cocos2d.h>
USING_NS_CC;

class FloatText: public Node
{
public:
	FloatText(){}

	~FloatText(){}

	static FloatText* create(const std::string& text,const int fontSize,Point begin);

	bool init(const std::string& text,int fontSize,Point begin);

	void floatIn(const int delay,std::function<void()> callback);

	void floatOut(const int delay,std::function<void()> callback);

	void floatInOut(const int speed,const int delay,std::function<void()> callback);
private:
	Point _begin;
	Label *_label;
};

#endif