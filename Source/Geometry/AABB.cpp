#include "stdafx.h"
#include "AABB.h"
#include "Triangle3d.h"


AABB::AABB()
{

	//_min = Vect3d(FLT_MIN, FLT_MIN, FLT_MIN);
	//_max = Vect3d(FLT_MAX, FLT_MAX, FLT_MAX);
	_max = Vect3d(100,100,100);
	_min = Vect3d(-100,-100,-100);

}

AABB::AABB(const Vect3d & min, const Vect3d & max) : _min(min), _max(max)
{
}

AABB::AABB(const AABB & aabb) : _min(aabb._min), _max(aabb._max)
{
}

AABB::~AABB()
{
}

Vect3d AABB::getCenter()
{
	Vect3d diagonal(_max.add(_min));

	return Vect3d(diagonal.getX() / 2, diagonal.getY() / 2, diagonal.getZ() / 2);
}

Vect3d AABB::getExtent()
{

	Vect3d centro = this->getCenter();
	return Vect3d(this->getMax().sub(centro));

}

AABB & AABB::operator=(const AABB & orig)
{
	_min = orig._min;
	_max = orig._max;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const AABB& aabb)
{
	os << "Maximum: " << aabb._max << ", minimum: " << aabb._min;
	return os;
}