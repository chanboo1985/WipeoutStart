#include "GameScene.h"
#include "Layer/GameLayer.h"
USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	this->addChild(GameLayer::create());
	return true;
}
