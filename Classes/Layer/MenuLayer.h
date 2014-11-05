#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__
#include <cocos2d.h>
USING_NS_CC;
class MenuLayer : public Layer
{
public:
	MenuLayer(){}

	~MenuLayer(){}

	virtual bool init();

	CREATE_FUNC(MenuLayer);
private:
	void startGame();
};

#endif