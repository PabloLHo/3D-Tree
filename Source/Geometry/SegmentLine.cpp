#include "stdafx.h"
#include "SegmentLine.h"

#include "Line.h"
#include "RayLine.h"

// Public methods

SegmentLine::SegmentLine()
{
}

SegmentLine::SegmentLine(const Point& a, const Point& b) : _orig(a), _dest(b)
{
}

SegmentLine::SegmentLine(const SegmentLine& segment) : _orig(segment._orig), _dest(segment._dest)
{
}

SegmentLine::SegmentLine(double ax, double ay, double bx, double by) : _orig(ax, ay), _dest(bx, by)
{
}

SegmentLine::~SegmentLine()
{
}

SegmentLine & SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}

bool SegmentLine::segmentIntersection(SegmentLine& l)
{

	Point a = this->getA();
	Point b = this->getB();
	Point c = l.getA();
	Point d = l.getB();
	if (a.colinear(c, d) || b.colinear(c, d) || c.colinear(a, b) || d.colinear(a, b)) {
		return false;
	}
	else {
		return (a.left(c, d) xor b.left(c, d) && c.left(a, b) xor d.left(a, b));
	}

}

double SegmentLine::getC()
{
	double pendiente = this->slope();
	if (pendiente == FLT_MAX)
		return  FLT_MAX;

	return this->getA().getY() - this->slope() * this->getA().getX();
}

bool SegmentLine::distinct(SegmentLine & segment)
{
	return !equal(segment);
}

float SegmentLine::distPointSegment(Point& point)
{
	Vect2d* d = new Vect2d((this->getB() - this->getA()).getX(), (this->getB() - this->getA()).getY());
	float t0 = d->dot(*new Vect2d(point.getX() - this->getA().getX(), point.getY() - this->getA().getY())) / d->dot(*d);
	float distance;
	if (t0 < 0 || BasicGeometry::equal(t0, 0.0)) {

		Vect2d* aux = new Vect2d(point.getX() - this->getA().getX(), point.getY() - this->getA().getY());
		distance = aux->getModule();

	}
	else if (t0 > 1 || BasicGeometry::equal(t0, 1.0)) {

		Vect2d* aux = new Vect2d(point.getX() - this->getB().getX(), point.getY() - this->getB().getY());
		distance = aux->getModule();

	}
	else {
		
		Vect2d* aux = new Vect2d(point.getX() - (this->getA().getX() + d->scalarMult(t0).getX()), point.getY() - (this->getA().getY() + d->scalarMult(t0).getY()));
		distance = aux->getModule();

	}

	return distance;
}

bool SegmentLine::equal(SegmentLine & segment)
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

Point SegmentLine::getPoint(double t)
{
    return Point(this->getA() + (this->getB() - this->getA()).scalarMult(t));
}

bool SegmentLine::impSegmentIntersection(SegmentLine& segment)
{
	Point a = this->getA();
	Point b = this->getB();
	Point c = segment.getA();
	Point d = segment.getB();
	if (a.isBetween(c, d) || b.isBetween(c, d) || c.isBetween(a, b) || d.isBetween(a, b)) {
		return true;
	}
	else {
		return (a.left(c, d) xor b.left(c, d) && c.left(a, b) xor d.left(a, b));
	}
    return true;

}

bool SegmentLine::isHorizontal()
{
	if(BasicGeometry::equal(this->getA().getY(), this->getB().getY()))
		return true;
	return false;
}

bool SegmentLine::isVertical()
{

	if (BasicGeometry::equal(this->getA().getX(), this->getB().getX()))
		return true;
	return false;

}

double SegmentLine::slope()
{
	
	if(glm::epsilonEqual((float)this->getA().getX(), (float)this->getB().getX(), glm::epsilon<float>()))
		return (this->getB().getY() - this->getA().getY()) / (this->getB().getX() - this->getA().getX());
	else {
		return FLT_MAX;
	}

}

// Protected methods

std::ostream& operator<<(std::ostream& os, const SegmentLine& segment)
{
	os << "Point A: " << segment._orig << ", Point B: " << segment._dest << "\n";

	return os;
}

// Protected methods

float SegmentLine::getDistanceT0(Vect2d& point)
{
	return 0.0f;
}

bool SegmentLine::intersects(const Point& p1,const Point& p2, float& s, float& t) {
	Vect2d* cd = new Vect2d(p2.getX() - p1.getX(), p2.getY() - p1.getY());
	Vect2d* ab = new Vect2d(this->getB().getX() - this->getA().getX(), this->getB().getY() - this->getA().getY());
	Vect2d* ac = new Vect2d(p1.getX() - this->getA().getX(), p1.getY() - this->getA().getY());
	if (BasicGeometry::equal(0.0, (cd->getX() * ab->getY() - ab->getX() * cd->getY()))) {
		return false;
	}
	s = ((cd->getX() * ac->getY() - ac->getX() * cd->getY()) / (cd->getX() * ab->getY() - ab->getX() * cd->getY()));
	t = ((ab->getX() * ac->getY() - ac->getX() * ab->getY()) / (cd->getX() * ab->getY() - ab->getX() * cd->getY()));
	return true;
}


bool SegmentLine::intersects(const RayLine& ray, Point &res) {
	float s;
	float t;
	if (this->intersects(ray.getA(), ray.getB(), s, t)) {
		if (((0 < s && s < 1) || BasicGeometry::equal(0.0,s) || BasicGeometry::equal(1.0,s)) && (t > 0 || BasicGeometry::equal(t,0.0))) {
			res = this->getPoint(s);
			return true;
		}
		return false;
	}
}

bool SegmentLine::intersects(const Line& r, Point& res)
{
	float s, t;
	if (intersects(r._orig, r._dest, s, t)) {
		if ((0 < s && s < 1) || BasicGeometry::equal(0.0, s) || BasicGeometry::equal(1.0, s)) {
			res = this->getPoint(s);
			return true;
		}
	}
	return false;
}

bool SegmentLine::intersects(const SegmentLine& r, Point& res)
{
	float s, t;
	if (intersects(r._orig, r._dest, s, t)) {
		if (((0 < s && s < 1) || BasicGeometry::equal(0.0, s) || BasicGeometry::equal(1.0, s)) && ((0 < t && t < 1) || BasicGeometry::equal(0.0, t) || BasicGeometry::equal(1.0, t))) {
			res = this->getPoint(s);
			return true;
		}
	}
	return false;
}