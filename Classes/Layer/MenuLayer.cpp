#include "MenuLayer.h"
#include "Scene/GameScene.h"
#include "Util/GameData/GameData.h"

USING_NS_CC;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *bg = Sprite::create("bg_menuscene.jpg");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bg,-1);

	MenuItemImage *startBtn = MenuItemImage::create("menu_start.png","menu_start.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	Menu *menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame()
{
	GameData::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());
}