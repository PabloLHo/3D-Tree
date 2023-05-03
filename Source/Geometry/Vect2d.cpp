#include "stdafx.h"
#include "Vect2d.h"

// Public methods

Vect2d::Vect2d(const Point& point) : Point(point)
{
}

Vect2d::Vect2d(const Vect2d& v) : Point(v._x, v._y)
{
}

Vect2d::~Vect2d()
{
}

double Vect2d::dot(Vect2d& b)
{
	
	return this->getX() * b.getX() + this->getY() * b.getY();
}

Vect2d & Vect2d::operator=(const Vect2d & vector)
{
	Point::operator=(vector);

	return *this;
}

Vect2d Vect2d::operator+(const Vect2d& b)
{
	
	return Vect2d(this->getX() + b._x, this->getY() + b._y);

}

Vect2d Vect2d::operator-(const Vect2d& b)
{

	return Vect2d(this->getX() - b._x, this->getY() - b._y);

}

Vect2d Vect2d::scalarMult(double t){
	
	return Vect2d(Point(this->getX() * t, this->getY() * t));

}