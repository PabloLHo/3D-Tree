#include "stdafx.h"
#include "BasicGeometry.h"
#include "RandomUtilities.h"
#include "Line3d.h"

Line3d::Line3d()
{
}

Line3d::Line3d(Vect3d & orig, Vect3d & dest)
	: Edge3d(orig, dest)
{
}

Line3d::Line3d(const Line3d & line)
	: Edge3d(line)
{
}

Line3d::~Line3d()
{
}


double Line3d::distance(Line3d& line){

	Vect3d *q = new Vect3d(this->getOrigin());
	Vect3d *q2 = new Vect3d(line.getOrigin());

	Vect3d *v = new Vect3d(getPoint(10));
	Vect3d *v2 = new Vect3d(line.getPoint(10));
	Vect3d aux = v->xProduct(*v2);

    return (q->sub(*q2).dot(aux)) / v->xProduct(*v2).module();

}

Line3d Line3d::normalLine(Vect3d& point)
{
	double l = 0;
	Vect3d v = this->_dest.sub(this->_orig);

	if (v.module() == 1) {
		Vect3d aux = point.sub(this->_orig);
		l = v.dot(aux);
	}
	else {
		Vect3d aux = point.sub(this->_orig);
		l = (v.dot(aux)) / (v.dot(v));
	}

	v = v.scalarMul(l);
	Vect3d aux = this->_orig.add(v);
	//Vect3d u = point.sub(aux);
	//Vect3d aux2 = point.add(u);

	return Line3d(point, aux);
}

double Line3d::distance(Vect3d& p) {

	double l = 0;
	Vect3d v = this->_dest.sub(this->_orig);

	if (v.module() == 1) {
		Vect3d aux = p.sub(this->_orig);
		l = v.dot(aux);
	}
	else {
		Vect3d aux = p.sub(this->_orig);
		l = (v.dot(aux)) / (v.dot(v));
	}

	v = v.scalarMul(l);
	Vect3d a = this->_orig.add(v);
	Vect3d aux = p.sub(a);

	return aux.module();
}

bool Line3d::isParallel(Line3d& l) {

	Vect3d puntoL1 = this->getPoint(RandomUtilities::getUniformRandom(-100, 100));
	Vect3d puntoL2 = l.getPoint(RandomUtilities::getUniformRandom(-100, 100));

	//if (BasicGeometry::equal(0.0, distance(l))) {

	//	return false;

	//}

	if (BasicGeometry::equal(puntoL1.getX() / puntoL2.getX(), puntoL1.getY() / puntoL2.getY()) && BasicGeometry::equal(puntoL1.getZ() / puntoL2.getZ(), puntoL1.getY() / puntoL2.getY())) {

		return true;

	}

	return false;

}


bool Line3d::isPerpendicular(Line3d& l) {

	Vect3d destino1(getDestination());
	Vect3d destino2(l.getDestination());

	Vect3d* v = new Vect3d(getOrigin().sub(destino1));
	Vect3d* v2 = new Vect3d(l.getOrigin().sub(destino2));
	float valor = v->dot(*v2);
	if (BasicGeometry::equal(0.0, v->dot(*v2))) {

		return true;

	}

	return false;

}

Line3d & Line3d::operator=(const Line3d & line)
{
	if (this != &line)
	{
		Edge3d::operator=(line);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Line3d& line)
{
	std::cout << "Line -> Origin: " << line._orig << ", Destination: " << line._dest;
	return os;
}

