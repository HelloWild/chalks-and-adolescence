#include "LoadScene.h"
#include "ConfigUtil.h"
#include "BattleScene.h"
#include "PrepareScene.h"

USING_NS_CC;

LoadScene::LoadScene() :loadState(LoadState::NA), animationState(AnimationState::NA), loadedNum(0), totalNum(0), logo(nullptr)
{
}

bool LoadScene::init()
{
	if (!Scene::init())
		return false;
	Director::getInstance()->getTextureCache()->addImage(LOAD_SCENE_BACKGROUND);
	logo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(LOAD_SCENE_BACKGROUND));
	logo->setPosition(config::visibleSize / 2);
	logo->setOpacity(0.0f);
	this->addChild(logo);
	animationState = AnimationState::FADE_IN;
	logo->runAction(Sequence::create(DelayTime::create(0.4f), FadeIn::create(1.0f), DelayTime::create(2.0f), CallFuncN::create([&](Node* sender) { animationState = AnimationState::WAIT_LOADING; }), nullptr));
	scheduleUpdate();
	return true;
}

void LoadScene::onEnter()
{
	Scene::onEnter();
	textureVector.push_back(BACKGROUNG_TEXTURE);
	textureVector.push_back(STUDENT_1);
	textureVector.push_back(STUDENT_2);
	textureVector.push_back(STUDENT_3);
	textureVector.push_back(STUDENT_4);
	textureVector.push_back(STUDENT_5);
	textureVector.push_back(STUDENT_6);
	totalNum = 1 + textureVector.size();
	loadState = LoadState::LOADING;
	for (auto textureName : textureVector)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(textureName, [&](cocos2d::Texture2D* texture)
		{
			loadedNum += 1;
		});
	}
	Director::getInstance()->getTextureCache()->addImageAsync(MAIN_TEXTURE_PNG, [&](cocos2d::Texture2D* texture)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAIN_TEXTURE_PLIST, texture);
		loadedNum += 1;
	});
}

void LoadScene::update(float delta_time)
{
	if (loadState == LoadState::LOADING && loadedNum == totalNum)
		loadState = LoadState::LOADED;
	if (loadState == LoadState::LOADED && animationState == AnimationState::WAIT_LOADING)
	{
		animationState = AnimationState::FADE_OUT;
		logo->runAction(Sequence::create(FadeOut::create(1.0f), CallFuncN::create([&](Node* sender)
		{
			Director::getInstance()->replaceScene(BattleScene::create());
		}), nullptr));
	}
}