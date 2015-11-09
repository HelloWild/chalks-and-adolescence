#pragma once
#include "BaseObject.h"
#include "ConfigUtil.h"

enum class StudentState
{
	NA,
	STU1,
	STU2,
	STU3,
	STU4,
	STU5,
	STU6,
};

enum class StudentDoing
{
	GOOD,
	WRONG,
	ELSE

};

enum class AttackState
{
	NA,
	ATTACK
};

class Student : public BaseObject
{
public:
	static Student* create(StudentState student_state = StudentState::NA);
	Student(StudentState student_state);
	virtual bool init() override;
	virtual void initState();
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void update(float delta_time) override;

	virtual void onContact(Message& message) override;
	virtual void initMessage() override;
	virtual void updateStateMachine(float delta_time);
	virtual void setState(StudentState student_state);
	virtual void enterState(StudentState student_state);
	virtual void exitState();

	void addBird();
//	virtual void onContact(Message& message) override;
private:
	cocos2d::Sprite* desk_sprite_;
	StudentState mStudentState;
	AttackState m_attack_state_;
	StudentDoing m_student_doing_;
};

