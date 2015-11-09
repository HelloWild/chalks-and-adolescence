#pragma once

#include "Leap.h"
#include "cocos2d.h"
#include <queue>

using namespace Leap;

//
//class ChalkInThrowType {
//public:
//	MyPoint s;
//	MyPoint v;
//	ChalkInThrowType(const MyPoint & s_, const MyPoint & v_) : s(s_), v(v_) {}
//};
//
//
//class ChalkInHand {
//public:
//	std::vector<MyPoint> chalk;
//
//public:
//	void addChalk(const MyPoint & C);
//	size_t size();
//	void throwChalk(std::queue<ChalkInThrowType> & chalkInThrow);
//};

enum class HandState
{
	EMPTY,
	HOLD,
	WAIT_THROW,
	THROW
};


class SampleListener : public Listener
{
public:
	virtual void onInit(const Controller&) override;
	virtual void onConnect(const Controller&) override;
	virtual void onDisconnect(const Controller&) override;
	virtual void onExit(const Controller&) override;
	virtual void onFrame(const Controller&) override;
	virtual void onFocusGained(const Controller&) override;
	virtual void onFocusLost(const Controller&) override;
	virtual void onDeviceChange(const Controller&) override;
	virtual void onServiceConnect(const Controller&) override;
	virtual void onServiceDisconnect(const Controller&) override;
	static int scraft();
	static cocos2d::Vec3 getHandPosition();
	static cocos2d::Vec3 getHandSpeed();
	static HandState getHandState();

//	static bool getChalkInThrow(ChalkInThrowType& chalk);
//	static bool isInHand();
//	static int scraft();
//	static MyPoint getHandPosition();
//
//	static MyPoint Myfinger[3];
//	static bool status;
//	static MyPoint handSpeed;
//	static MyPoint handPosition;
//	static std::queue<ChalkInThrowType> chalkInThrow;
//	static ChalkInHand inHand;
private:
	static cocos2d::Vec3 Myfinger[3];
	static cocos2d::Vec3 handPosition;
	static cocos2d::Vec3 handSpeed;
	static HandState handState;
};

