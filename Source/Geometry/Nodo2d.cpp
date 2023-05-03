#include "stdafx.h"
#include "Nodo2d.h"

Nodo2d::Nodo2d()
{
	izq = nullptr;
	drch = nullptr;
	nivel = -1;
	coordenadaDivisoria = -1;
}

Nodo2d::Nodo2d(int anivel, Nodo2d ni, Nodo2d nd, SegmentLine lineaDivision, double _coordenada) {
	nivel = anivel;
	izq = new Nodo2d(ni);
	drch = new Nodo2d(nd);
	lineaDivisoria = lineaDivision;
	coordenadaDivisoria = _coordenada;

	hoja = false;
}

Nodo2d::Nodo2d(int anivel, Point punto) {
	nivel = anivel;
	izq = nullptr;
	drch = nullptr;
	this->punto = punto;

	hoja = true;
}


Nodo2d::Nodo2d(const Nodo2d& Nodo2d) {
	nivel = Nodo2d.nivel;
	izq = Nodo2d.izq;
	drch = Nodo2d.drch;
	lineaDivisoria = Nodo2d.lineaDivisoria;
}

Nodo2d::~Nodo2d()
{
	//delete izq, drch;
}

void Nodo2d::asignarDrch(Nodo2d drch) {

	this->drch = new Nodo2d(drch);

}

void Nodo2d::asignarIzq(Nodo2d izq) {

	this->izq = new Nodo2d(izq);

}

void Nodo2d::asignarPunto(Point punto) {

	this->punto = punto;

}