#pragma once

#include "cocos2d.h"

enum class HandState
{
	EMPTY,
	HOLD,
	WAIT_THROW,
	THROW
};

class MotionData
{
public:
	static MotionData* getInstance();
	MotionData();
	~MotionData();
	cocos2d::Vec3 handPosition;
	cocos2d::Vec3 handSpeed;
	HandState handState;
private:
	static MotionData* motion_data_;
};

