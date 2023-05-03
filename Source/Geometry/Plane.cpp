#include "stdafx.h"
#include "Plane.h"
#include "BasicGeometry.h"


Plane::Plane(Vect3d & p, Vect3d & u, Vect3d & v, bool arePoints)
{
	if (!arePoints)			// Vectors: pi = p + u * lambda + v * mu 
	{			
		_a = p;
		_b = u.add(_a);
		_c = v.add(_a);
	}
	else 
	{						// 3 points in the plane
		_a = p;
		_b = u;
		_c = v;
	}
}

Plane::Plane(const Plane & plane): _a(plane._a), _b(plane._b), _c(plane._c)
{
}

Plane::~Plane()
{
}

bool Plane::coplanar(Vect3d& point){  

	if (BasicGeometry::equal(0.0, distance(point))) {

		return true;

	}

	return false;

}

double Plane::distance(Vect3d & point)
{

	double landa = -(this->getNormal().dot(point) + this->getD());
	if (!BasicGeometry::equal(1.0, this->getNormal().module())) {

		Vect3d normal(this->getNormal());
		landa = landa / this->getNormal().dot(normal);

	}

    return this->getNormal().scalarMul(landa).module();
}    

double Plane::getA()
{
	return (BasicGeometry::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
}

double Plane::getB()
{
	return (BasicGeometry::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));	
}

double Plane::getC()
{
	return (BasicGeometry::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
}

Vect3d Plane::getNormal()
{
   
    return Vect3d(this->getA(), this->getB(), this->getC());
}

bool Plane::intersect(Plane & plane, Line3d & line)
{

	Vect3d *aux = new Vect3d(plane.getNormal());
	Vect3d* normal = new Vect3d(this->getNormal().xProduct(*aux));
	double det = BasicGeometry::determinant3x3(this->getA(), this->getB(), this->getC(), plane.getA(), plane.getB(), plane.getC(), normal->getX(), normal->getY(), normal->getZ());
	if (BasicGeometry::equal(0.0, det)) {

		return false;

	}
	double x0 = (plane.getD() * BasicGeometry::determinant2x2(this->getB(), this->getC(), normal->getY(), normal->getZ()) - this->getD() * BasicGeometry::determinant2x2(plane.getB(), plane.getC(), normal->getY(), normal->getZ())) / det;
	double y0 = (plane.getD() * BasicGeometry::determinant2x2(normal->getX(), normal->getZ(), this->getA(), this->getC()) - this->getD() * BasicGeometry::determinant2x2(normal->getX(), normal->getZ(), plane.getA(), plane.getC())) / det;
	double z0 = (plane.getD() * BasicGeometry::determinant2x2(this->getA(), this->getB(), normal->getX(), normal->getY()) - this->getD() * BasicGeometry::determinant2x2(plane.getA(), plane.getB(), normal->getX(), normal->getY())) / det;

	Vect3d p0(x0, y0, z0);
	Vect3d p1(x0 + normal->getX(), y0 + normal->getY(), z0 + normal->getZ());

	Line3d* resultado = new Line3d(p0, p1);
	line = *resultado;

    return true;

}

bool Plane::intersect(Line3d& line, Vect3d& point)
{
	double l = 0;
	Vect3d* aux = new Vect3d(line.getOrigin());
	Vect3d v = line.getDestination().sub(*aux);

	if (this->getNormal().dot(v) == 0) {
		return false;
	}

	if (v.module() == 1) {
		l = -(this->getNormal().dot(*aux) + this->getD());
	}
	else {
		l = (-(this->getNormal().dot(*aux) + this->getD())) / this->getNormal().dot(v);
	}

	Vect3d resultado = v.scalarMul(l);
	point = line.getOrigin().add(resultado);

	return true;
}

Vect3d Plane::reflectedPoint(Vect3d& v)
{

	double lamda = -2 * (this->getNormal().dot(v) + this->getD());

	if (!BasicGeometry::equal(1.0, this->getNormal().module())) {

		Vect3d normal(this->getNormal());
		lamda = lamda / this->getNormal().dot(normal);

	}
	Vect3d aux(this->getNormal().scalarMul(lamda));
	Vect3d q = v.add(aux);

	return q;

}

bool Plane::intersect(Plane& pa, Plane& pb, Vect3d& pinter)
{
	//XXXX
	return true;
}

bool intersect(Plane& pa, Plane& pb, Vect3d& pinter)
{
	//XXXX
    return true; 
}

Plane & Plane::operator=(const Plane & plane)
{
	if (this != &plane)
	{
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Plane& plane)
{
	os << "Plane -> a: " << plane._a << ", b: " << plane._b << ", c: " << plane._c;
	return os;
}