#ifndef __TOP_MENU_H__
#define __TOP_MENU_H__
#include <cocos2d.h>
using namespace cocos2d;
class TopMenu : public Node
{
public:
	TopMenu(){}

	~TopMenu(){}

	virtual bool init();

	CREATE_FUNC(TopMenu);

	void refresh();
private:
	Label* highestScore;//历史最高分

	Label* level;//当前关卡

	Label* targetScore;//目标分数

	Label* curScore;//当前分数
};

#endif