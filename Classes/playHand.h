#pragma once
/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
#include "Leap.h"
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


#define _GET_CHALK_MAXLENGTH_ 20.0
using namespace Leap;

//double x, y, z;

const double INF = 1e5;

class MyPoint {
public:
	double x, y, z;
	MyPoint(double x_ = 0, double y_ = 0, double z_ = 0);
	inline
		double distance(const MyPoint & P) const;

	void out();
};



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
		NOHAND= -1,
		UNUSED = -2
	};
private:
	MyPoint Speed;
	MyPoint Position;
	MyPoint playFinger[3];
	int status;
};
