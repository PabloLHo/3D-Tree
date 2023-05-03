#include "stdafx.h"
#include "KDTree.h"

KDTree::KDTree()
{
}

KDTree::KDTree(PointCloud* nP){

	raiz2D = construir2DTree(nP->getPoints(), 0);

}

KDTree::KDTree(PointCloud3d* nP) {

	raiz3D = construir3DTree(nP->getPoints(), 0);

}

KDTree::KDTree(const KDTree& kdTree){

}

KDTree::~KDTree()
{
}

Nodo3d KDTree::construir3DTree(std::vector<Vect3d> puntos, int nivel) {

	if (puntos.size() > 1) {

		Nodo3d Nodo3dIzq, Nodo3dDrch;
		int mitad = puntos.size() / 2 - 1;
		double coordenada;

		switch (nivel % 3) {
			//División por X
			case 0:
				std::sort(puntos.begin(), puntos.end(), &compX);
				coordenada = puntos[mitad].getX();
				break;
			//Divisón por Y
			case 1:
				std::sort(puntos.begin(), puntos.end(), &compY);
				coordenada = puntos[mitad].getY();
				break;
			//Divisón por Z
			case 2:
				std::sort(puntos.begin(), puntos.end(), &compZ);
				coordenada = puntos[mitad].getZ();
				break;
		}
		
		std::vector<Vect3d> l1, l2;
		std::copy(puntos.begin(), puntos.begin() + mitad + 1, back_inserter(l1));
		std::copy(puntos.begin() + mitad + 1, puntos.end(), back_inserter(l2));

		std::cout << nivel << " - division: " << coordenada << std::endl;

		Plane p = determinarPlanoDiv(nivel, coordenada);

		Nodo3dIzq = construir3DTree(l1, nivel + 1);
		Nodo3dDrch = construir3DTree(l2, nivel + 1);
		return Nodo3d(nivel, Nodo3dIzq, Nodo3dDrch, p, coordenada);

	}
	else
		return Nodo3d(nivel, puntos[0]);

}

Nodo2d KDTree::construir2DTree(std::vector<Point> puntos, int nivel) {

	if (puntos.size() > 1) {

		Nodo2d nodoIzq, nodoDrch;
		int mitad = puntos.size() / 2 - 1;
		double coordenada;

		switch (nivel % 2) {
			//División por X
		case 0:
			std::sort(puntos.begin(), puntos.end(), &comp2X);
			coordenada = puntos[mitad].getX();
			break;
			//Divisón por Y
		case 1:
			std::sort(puntos.begin(), puntos.end(), &comp2Y);
			coordenada = puntos[mitad].getY();
			break;
		}

		std::vector<Point> l1, l2;
		std::copy(puntos.begin(), puntos.begin() + mitad + 1, back_inserter(l1));
		std::copy(puntos.begin() + mitad + 1, puntos.end(), back_inserter(l2));

		SegmentLine p = determinarSegmentoDiv(nivel, coordenada);

		nodoIzq = construir2DTree(l1, nivel + 1);
		nodoDrch = construir2DTree(l2, nivel + 1);
		return Nodo2d(nivel, nodoIzq, nodoDrch, p, coordenada);

	}
	else
		return Nodo2d(nivel, puntos[0]);

}

bool KDTree::compX(const Vect3d& v1, const Vect3d& v2) {

	Vect3d aux = v1;
	Vect3d aux2 = v2;


	return aux.getX() < aux2.getX();

}

bool KDTree::compY(const Vect3d& v1, const Vect3d& v2) {

	Vect3d aux = v1;
	Vect3d aux2 = v2;


	return aux.getY() < aux2.getY();

}

bool KDTree::compZ(const Vect3d& v1, const Vect3d& v2) {

	Vect3d aux = v1;
	Vect3d aux2 = v2;


	return aux.getZ() < aux2.getZ();

}

bool KDTree::comp2X(const Point& v1, const Point& v2) {

	Point aux = v1;
	Point aux2 = v2;


	return aux.getX() < aux2.getX();

}

bool KDTree::comp2Y(const Point& v1, const Point& v2) {

	Point aux = v1;
	Point aux2 = v2;


	return aux.getY() < aux2.getY();

}

Plane KDTree::determinarPlanoDiv(int nivel, double coordenada) {

	int eje = nivel % 3;

	double aleatorio = 5;

	Vect3d v1((2 - eje) * (1 - eje) * coordenada/2 + eje * aleatorio, eje * (2 - eje) * coordenada + (eje - 1) * aleatorio, eje * (eje - 1) * coordenada / 2 + (2 - eje) * aleatorio);
	Vect3d v2((2 - eje) * (1 - eje) * coordenada/2 + eje * aleatorio, eje * (2 - eje) * coordenada + (eje - 1) * aleatorio, eje * (eje - 1) * coordenada / 2 + (2 - eje) * aleatorio);
	Vect3d v3((2 - eje) * (1 - eje) * coordenada/2 + eje * aleatorio, eje * (2 - eje) * coordenada + (eje - 1) * aleatorio, eje * (eje - 1) * coordenada / 2 + (2 - eje) * aleatorio);

	return Plane(v1, v2, v3, true);

}

SegmentLine KDTree::determinarSegmentoDiv(int nivel, double coordenada) {

	int eje = nivel % 2;

	int aleatorio = 5;

	Point v1((1 - eje) * coordenada + eje * aleatorio, eje * coordenada + (eje - 1) * aleatorio);
	Point v2((1 - eje) * coordenada + eje * aleatorio, eje * coordenada + (eje - 1) * aleatorio);


	return SegmentLine(v1,v2);
}