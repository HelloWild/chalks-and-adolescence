#pragma once
#include "BaseObject.h"

enum class NewChalkState
{
	NA,
	ON_HAND,
	THROW
};

class NewChalk:public BaseObject
{
public:
	static NewChalk* create(NewChalkState chalk_state);
	NewChalk(NewChalkState chalk_state);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void update(float delta_time) override;
	virtual void enterState(NewChalkState state);
	virtual void setState(NewChalkState state);
	virtual void exitState();
	NewChalkState getState();
	virtual void onContact(Message& message) override;
	virtual void initMessage() override;
	void setVelocity(cocos2d::Vec3 velocity);

	//	virtual void updateStateMachine(float delta_time);
	//	virtual void setState(StudentState student_state);
	//	virtual void enterState(StudentState student_state);
	//	virtual void exitState();
private:
	NewChalkState m_chalk_state_;
	cocos2d::Vec3 position;
	cocos2d::Vec3 velocity;
	float zVelocity;
	float rotateVelocity;
};

