#pragma once

#include "cocos2d.h"

enum class LoadState
{
	NA,
	LOADING,
	LOADED
};

enum class AnimationState
{
	NA,
	FADE_IN,
	WAIT_LOADING,
	FADE_OUT
};

class LoadScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(LoadScene);
	LoadScene();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void update(float delta_time) override;
private:
	LoadState loadState;
	AnimationState animationState;
	int loadedNum;
	int totalNum;
	cocos2d::Sprite* logo;
	std::vector<std::string> textureVector;
};

