#include "stdafx.h"
#include "Point.h"

// Public methods

Point::Point()
{
	_x = DEFAULT_VALUE;
	_y = DEFAULT_VALUE;
}

Point::Point(double x, double y, bool polar)
{
	if (!polar)
	{
		_x = x; _y = y;
	} 
	else
	{
		_x = getModule();
		_y = getAlpha();
	}
}

Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

Point::~Point()
{
}

Point::PointClassification Point::classify(Point & p0, Point & p1)
{

	Point a(p1.getX() - p0.getX(), p1.getY() - p0.getY());
	Point b(this->getX() - p0.getX(), this->getY() - p0.getY());
	double solucion = a.getX() * b.getY() - b.getX() * a.getY();
	
	if (solucion > 0.0)
		return PointClassification::LEFT;
	if (solucion < 0.0)
		return PointClassification::RIGHT;
	if ((a.getX() * b.getX() < 0.0) || (a.getY() * b.getY() < 0.0))
		return PointClassification::BACKWARD;
	if (a.getModule() < b.getModule())
		return PointClassification::FORWARD;
	if (this->equal(p0))
		return PointClassification::ORIGIN;
	if(this->equal(p1))
		return PointClassification::DEST;
	return PointClassification::BETWEEN;
}

bool Point::colinear(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result != PointClassification::LEFT) && (result != PointClassification::RIGHT);
}

double Point::distance(Point & p)
{

	return glm::sqrt(std::pow((_x - p.getX()),2) + std::pow((_y - p.getY()),2));
}

double Point::getAlpha()
{
	
	return glm::atan(_y / _x);

}

double Point::getModule()
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}

bool Point::leftAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::LEFT) || (result != PointClassification::RIGHT);
}

Point & Point::operator=(const Point & point)
{
	_x = point._x;
	_y = point._y;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	os << "Coordinate X: " << point._x << ", coordinate Y: " << point._y;

	return os;
}

bool Point::rightAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::RIGHT) || (result != PointClassification::LEFT);
}

double Point::slope(Point & p)
{
	
    return (p.getY() - this->getY()) / (p.getX() - this->getX());
}

double Point::triangleArea2(Point& a, Point& b)
{
	
	return (this->getX() * a.getY() - this->getY() * a.getX() + a.getX() * b.getY() - a.getY() * b.getX() + b.getX() * this->getY() - b.getY() * this->getX());
}

Point Point::operator+(const Point& b)
{

	return Point(this->getX() + b._x, this->getY() + b._y);

}

Point Point::operator-(const Point& b)
{

	return Point(this->getX() - b._x, this->getY() - b._y);

}

Point Point::scalarMult(double t)
{

	return Point(this->getX() * t, this->getY() * t);

}