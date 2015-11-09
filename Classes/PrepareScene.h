#pragma once

#include "cocos2d.h"

class PrepareScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(PrepareScene);
	PrepareScene();
	virtual bool init() override;
	virtual void update(float delta_time) override;
};

