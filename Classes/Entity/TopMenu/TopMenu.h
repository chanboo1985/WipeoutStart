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
	Label* highestScore;//��ʷ��߷�

	Label* level;//��ǰ�ؿ�

	Label* targetScore;//Ŀ�����

	Label* curScore;//��ǰ����
};

#endif