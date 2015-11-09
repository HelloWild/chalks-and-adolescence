/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <vector> 
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
#include "Leap.h"

#define _GET_CHALK_MAXLENGTH_ 20.0
#define _MIN_THROW_SPEED_ 150.0
using namespace Leap;

const double INF = 1e5;

double Mysqr(double x) {
	return x * x;
}

class MyPoint {
public:
	double x, y, z;
	MyPoint(double x_ = 0, double y_ = 0, double z_ = 0);
	inline
		double distance(const MyPoint & P) const;

	void out();
};

inline
MyPoint::MyPoint(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
}
double MyPoint::distance(const MyPoint & P) const {
	if (x > INF / 2 || y > INF / 2 || z > INF / 2) return INF;
	if (P.x > INF / 2 || P.y > INF / 2 || P.z > INF / 2) return INF;
	return sqrt(Mysqr(x - P.x) + Mysqr(y - P.y) + Mysqr(z - P.z));
}
void MyPoint::out() {
	printf("(%.3lf, %.3lf, %.3lf)\n", x, y, z);
}

class PlayerHand : public Listener {
public:
	virtual void onFrame(const Controller&);

	PlayerHand();
	int getStatus();
	MyPoint getSpeed();
	MyPoint getPosition();
	enum {
		HOLD = 0,
		EMPTY = 1,
		ERROR = -1,
		UNUSED = -2
	};
private:
	MyPoint Speed;
	MyPoint Position;
	MyPoint playFinger[3];
	int status;
	time_t pre_t;
};

PlayerHand::PlayerHand() {
	status = ERROR;
	Speed = MyPoint(0, 0, 0);
	Position = MyPoint(0, 0, 0);
	pre_t = time(NULL);
}
int PlayerHand::getStatus() {
	return status;
}

MyPoint PlayerHand::getSpeed() {
	return Speed;
}

MyPoint PlayerHand::getPosition() {
	return Position;
}

void PlayerHand::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();
	HandList hands = frame.hands();
	if (hands.begin() == hands.end()) {
		status = ERROR;
		return;
	}
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		const Hand hand = *hl;
		Position = MyPoint(hand.palmPosition().x + 960, hand.palmPosition().y * 2.8, hand.palmPosition().z);
		Speed = MyPoint(hand.palmVelocity().x, hand.palmVelocity().y, hand.palmVelocity().z);

		Arm arm = hand.arm();

		const FingerList fingers = hand.fingers();

		int tot = -1;
		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
			const Finger finger = *fl;
			tot++;
			if (tot == 3) break;
			for (int b = 3; b < 4; ++b) {
				Bone::Type boneType = static_cast<Bone::Type>(b);
				Bone bone = finger.bone(boneType);
				playFinger[tot].x = bone.nextJoint().x;
				playFinger[tot].y = bone.nextJoint().y;
				playFinger[tot].z = bone.nextJoint().z;
			}
		}
	}
	double t1 = playFinger[0].distance(playFinger[1]);
	double t2 = playFinger[0].distance(playFinger[2]);
	double t3 = playFinger[1].distance(playFinger[2]);
	int tmp = (t1 < _GET_CHALK_MAXLENGTH_ || t2 < _GET_CHALK_MAXLENGTH_ || t3 < _GET_CHALK_MAXLENGTH_) ? HOLD : EMPTY;
	if ((status == EMPTY && tmp == HOLD) && (time(NULL) - pre_t <= 2)) {
		status = EMPTY;
		return;
	}
	if (Speed.distance(MyPoint(0, 0, 0)) < _MIN_THROW_SPEED_ && status == HOLD) status = HOLD;
	else {
		if (tmp == EMPTY && status == HOLD) pre_t = time(NULL);
		status = tmp;
	}
}
