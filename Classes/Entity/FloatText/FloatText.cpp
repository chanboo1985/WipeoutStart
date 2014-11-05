#include "FloatText.h"

FloatText* FloatText::create(const std::string& text,int fontSize,Point begin)
{
	FloatText *ret = new FloatText;
	if (ret && ret->init(text,fontSize,begin))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FloatText::init(const std::string& text,const int fontSize,Point begin)
{
	if (!Node::init())
	{
		return false;
	}
	_begin = begin;
	_label = Label::create(text,"Verdana-Bold",fontSize);
	_label->setPosition(begin);
	this->addChild(_label);
	return true;
}

//文字从左侧飞入
void FloatText::floatIn(const int delay,std::function<void()> callback)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo *move = MoveTo::create(delay,ccp(visibleSize.width/2,_begin.y));
	CallFunc *call = CallFunc::create(callback);
	Sequence *action = Sequence::create(move,call,NULL);
	_label->runAction(action);
}

//文字飞出左侧屏幕
void FloatText::floatOut(const int delay,std::function<void()> callback)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo *move = MoveTo::create(delay,ccp(0,_begin.y));
	CallFunc *call = CallFunc::create(callback);
	CallFunc *del = CallFunc::create([this](){this->removeAllChildrenWithCleanup(true);});
	Sequence *action = Sequence::create(move,call,del,NULL);
	_label->runAction(action);
}

//文字先飞入再飞出
void FloatText::floatInOut(const int speed,const int delay,std::function<void()> callback)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo *moveIn = MoveTo::create(speed,ccp(visibleSize.width/2,_begin.y));
	DelayTime *dt = DelayTime::create(delay);
	MoveTo *moveOut = MoveTo::create(speed,ccp(0,_begin.y));
	CallFunc *call = CallFunc::create(callback);
	CallFunc *del = CallFunc::create([this](){this->removeAllChildrenWithCleanup(true);});
	Sequence* action = Sequence::create(moveIn,dt,moveOut,call,del,NULL);
	_label->runAction(action);
}