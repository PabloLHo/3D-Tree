#include "stdafx.h"
#include "Nodo.h"

Nodo::Nodo()
{
	izq = nullptr;
	drch = nullptr;
	nivel = -1;
}

Nodo::Nodo(int anivel, Nodo ni, Nodo nd, Plane planoDivision) {
	nivel = anivel;
	izq = new Nodo(ni);
	drch = new Nodo(nd);
	planoDivisorio = planoDivision;
}

Nodo::Nodo(int anivel, Vect3d punto) {
	nivel = anivel;
	izq = nullptr;
	drch = nullptr;
	punto3D = punto;
}


Nodo::Nodo(const Nodo& nodo) {
	nivel = nodo.nivel;
	izq = nodo.izq;
	drch = nodo.drch;
	planoDivisorio = nodo.planoDivisorio;
}

Nodo::~Nodo()
{
	delete izq, drch;
}

void Nodo::asignarDrch(Nodo drch) {

	this->drch = new Nodo(drch);

}

void Nodo::asignarIzq(Nodo izq) {

	this->izq = new Nodo(izq);

}

void Nodo::asignarPunto(Vect3d punto) {

	this->punto3D = punto;

}
