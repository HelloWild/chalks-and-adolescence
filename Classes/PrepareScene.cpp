#include "PrepareScene.h"
#include "BattleScene.h"
#include "ConfigUtil.h"

USING_NS_CC;

PrepareScene::PrepareScene()
{
}

bool PrepareScene::init()
{
	if (!Scene::init())
		return false;
	auto sprite = Sprite::create();
	sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(LOAD_SCENE_BACKGROUND));
	sprite->setPosition(config::visibleSize / 2);
	this->addChild(sprite);
	this->addChild(sprite);
	sprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFuncN::create([&](Node* sender)
	{
		Director::getInstance()->replaceScene(BattleScene::create());
	}), nullptr));

	return true;
}

void PrepareScene::update(float delta_time)
{
}