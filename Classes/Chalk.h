#pragma once
#include "BaseObject.h"

//enum class StudentState;

enum class ChalkState
{
	NA,
	ON_HAND,
	THROW
};


class Chalk:public BaseObject
{
public:
	static Chalk* create(ChalkState chalk_state);
	Chalk(ChalkState chalk_state);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void update(float delta_time) override;
	virtual void onContact(Message& message) override;
	virtual void initMessage() override;
	void setVelocity(cocos2d::Vec3 velocity);

//	virtual void updateStateMachine(float delta_time);
//	virtual void setState(StudentState student_state);
//	virtual void enterState(StudentState student_state);
//	virtual void exitState();
private:
	ChalkState m_chalk_state_;
};

