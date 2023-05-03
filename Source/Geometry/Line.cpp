#include "stdafx.h"
#include "Line.h"

#include "RayLine.h"
#include "SegmentLine.h"


Line::Line(const Point & a, const Point & b) : SegmentLine(a, b)
{
}

Line::Line(const Line & s) : SegmentLine(s)
{
}

Line::~Line()
{
}

double Line::distancePointLine(Point& p)
{
	Vect2d* d = new Vect2d((this->getB() - this->getA()).getX(), (this->getB() - this->getA()).getY());
	float t0 = d->dot(*new Vect2d(p.getX() - this->getA().getX(), p.getY() - this->getA().getY())) / d->dot(*d);

	Vect2d* aux = new Vect2d(p.getX() - (this->getA().getX() + d->scalarMult(t0).getX()), p.getY() - (this->getA().getY() + d->scalarMult(t0).getY()));

	return aux->getModule();

	/*return this->distPointSegment(p);*/
}

bool Line::intersects(Line& line, Point& intersection)
{
	float s;
	float t;
	if (SegmentLine::intersects(line.getA(), line.getB(), s, t)) {
		intersection = this->getPoint(s);
		return true;
	}
	return false;
}

bool Line::intersects(RayLine& rayline, Point& intersection)
{
	float s, t;
	if (SegmentLine::intersects(rayline.getA(), rayline.getB(), s, t)) {
		if ((0 < t || BasicGeometry::equal(t,0.0))) {
			intersection = this->getPoint(s);
			return true;
		}
	}
	return false;
}

bool Line::intersects(SegmentLine& segmento, Point& intersection)
{

	return segmento.intersects(*this,intersection);

}


bool Line::incorrectSegmentIntersection(SegmentLine& l)
{
	return false;
}

Line & Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
	os << "Line --->\n\tPoint A: " << line._orig << "\n\tPoint B: " << line._dest << "\n";

	return os;
}

bool Line::segmentIntersection(SegmentLine& l)
{
	if (l.segmentIntersection(*this)) {
		return true;
	}
	return false;
}