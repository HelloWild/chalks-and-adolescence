#pragma once

#include <cmath>

const double INF = 1e5;

inline double sqr(double x) {
	return x * x;
}

class MyPoint
{
public:
	double x, y, z;
	inline
		MyPoint(double x_ = 0, double y_ = 0, double z_ = 0) : x(x_), y(y_), z(z_) {}
	inline
		double distance(const MyPoint & P) const {
		if (x > INF / 2 || y > INF / 2 || z > INF / 2) return INF;
		if (P.x > INF / 2 || P.y > INF / 2 || P.z > INF / 2) return INF;
		return sqrt(sqr(x - P.x) + sqr(y - P.y) + sqr(z - P.z));
	}
};

