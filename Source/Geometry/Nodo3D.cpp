#include "stdafx.h"
#include "Nodo3d.h"

Nodo3d::Nodo3d()
{
	izq = nullptr;
	drch = nullptr;
	nivel = -1;
	coordenadaDivisoria = -1;
}

Nodo3d::Nodo3d(int anivel, Nodo3d ni, Nodo3d nd, Plane planoDivision, double _coordenada) {
	nivel = anivel;
	izq = new Nodo3d(ni);
	drch = new Nodo3d(nd);
	planoDivisorio = planoDivision;
	coordenadaDivisoria = _coordenada;
	
	hoja = false;
}

Nodo3d::Nodo3d(int anivel, Vect3d punto) {
	nivel = anivel;
	izq = nullptr;
	drch = nullptr;
	punto3D = punto;

	hoja = true;
}


Nodo3d::Nodo3d(const Nodo3d& Nodo3d) {
	nivel = Nodo3d.nivel;
	izq = Nodo3d.izq;
	drch = Nodo3d.drch;
	planoDivisorio = Nodo3d.planoDivisorio;
}

Nodo3d::~Nodo3d()
{
	//delete izq, drch;
}

void Nodo3d::asignarDrch(Nodo3d drch) {

	this->drch = new Nodo3d(drch);

}

void Nodo3d::asignarIzq(Nodo3d izq) {

	this->izq = new Nodo3d(izq);

}

void Nodo3d::asignarPunto(Vect3d punto) {

	this->punto3D = punto;

}
