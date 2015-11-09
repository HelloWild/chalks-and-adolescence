#pragma once

#include "cocos2d.h"
#include "Chalk.h"
#include "NewChalk.h"

class BattleScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(BattleScene);
	BattleScene();
	virtual ~BattleScene();
	virtual bool init() override;
	static BattleScene* getInstance();
	virtual void update(float delta_time) override;
	bool onContactBegin(cocos2d::PhysicsContact& contact);
protected:
	static BattleScene* battleScene;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	NewChalk* new_chalk_;
};

