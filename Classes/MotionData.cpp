#include "MotionData.h"

MotionData* MotionData::motion_data_ = nullptr;

MotionData* MotionData::getInstance()
{
	if (motion_data_ == nullptr)
		motion_data_ = new MotionData();
	return motion_data_;
}

MotionData::MotionData()
{
}


MotionData::~MotionData()
{
}
