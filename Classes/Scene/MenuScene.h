#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__
#include <cocos2d.h>
USING_NS_CC;
class MenuScene : public Scene
{
public:
	MenuScene(){}

	~MenuScene(){}
	
	virtual bool init();

	CREATE_FUNC(MenuScene);
};

#endif