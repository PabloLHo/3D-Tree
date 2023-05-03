#include "stdafx.h"
#include "RayLine.h"

#include "Line.h"

// Public methods

RayLine::RayLine(const Point& a, const Point& b) : SegmentLine(a, b)
{
}

RayLine::RayLine(const RayLine& ray) : SegmentLine(ray)
{
}

RayLine::~RayLine()
{
}

float RayLine::distanceToPoint(Point& point)
{
		Vect2d* d = new Vect2d((this->getB() - this->getA()).getX(), (this->getB() - this->getA()).getY());
		float t0 = d->dot(*new Vect2d(point.getX() - this->getA().getX(), point.getY() - this->getA().getY())) / d->dot(*d);
		float distance;
		if (t0 < 0 || BasicGeometry::equal(t0, 0.0)) {

			Vect2d* aux = new Vect2d(point.getX() - this->getA().getX(), point.getY() - this->getA().getY());
			distance = aux->getModule();

		}
		else {

			Vect2d* aux = new Vect2d(point.getX() - (this->getA().getX() + d->scalarMult(t0).getX()), point.getY() - (this->getA().getY() + d->scalarMult(t0).getY()));
			distance = aux->getModule();

		}

		return distance;

}

bool RayLine::incorrectSegmentIntersection(SegmentLine& segment)
{
	return false;
}

RayLine & RayLine::operator=(const RayLine & rayline)
{
	if (this != &rayline)
	{
		SegmentLine::operator=(rayline);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const RayLine& ray)
{
	os << "Point A: " << ray._orig << ", Point B: " << ray._dest << "\n";

	return os;
}

bool RayLine::intersects(RayLine& ray, Point& intersection)
{
	float s, t;
	if (SegmentLine::intersects(ray.getA(), ray.getB(), s, t)) {
		if ((0 < s || BasicGeometry::equal(s, 0.0)) && (0 < t || BasicGeometry::equal(t, 0.0))) {
			intersection = this->getPoint(s);
			return true;
		}
	}
	return false;
}

bool RayLine::intersects(Line& line, Point& intersection)
{
	return line.intersects(*this,intersection);
}

bool RayLine::intersects(SegmentLine& segment, Point& intersection)
{
	return segment.intersects(*this, intersection);
}