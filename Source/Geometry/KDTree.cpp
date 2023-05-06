#include "stdafx.h"
#include "KDTree.h"


KDTree::KDTree()
{
}

KDTree::KDTree(PointCloud* nP){

	raiz2D = construir2DTree(nP->getPoints(), 0, AABB());

}

KDTree::KDTree(PointCloud3d* nP) {

	raiz3D = construir3DTree(nP->getPoints(), 0, AABB());

}

KDTree::KDTree(const KDTree& kdTree){

}

KDTree::~KDTree()
{
}

Nodo3d KDTree::construir3DTree(std::vector<Vect3d> puntos, int nivel, AABB limites) {

	if (puntos.size() > 1) {

		Nodo3d Nodo3dIzq, Nodo3dDrch;
		int mitad;
		if (puntos.size() % 2 == 0)
			mitad = puntos.size() / 2 - 1;
		else
			mitad = puntos.size() / 2;

		double coordenada;
		AABB izq;
		AABB drch;


		switch (nivel % 3) {
			//División por X
			case 0:
				std::sort(puntos.begin(), puntos.end(), &compX);
				coordenada = puntos[mitad].getX();
				izq = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), limites.getMin().getZ()), Vect3d(coordenada, limites.getMax().getY(), limites.getMax().getZ()));
				drch = AABB(Vect3d(coordenada, limites.getMin().getY(), limites.getMin().getZ()), Vect3d(limites.getMax().getX(), limites.getMax().getY(), limites.getMax().getZ()));
				break;
			//Divisón por Y
			case 1:
				std::sort(puntos.begin(), puntos.end(), &compY);
				coordenada = puntos[mitad].getY();
				izq = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), limites.getMin().getZ()), Vect3d(limites.getMax().getX(), coordenada, limites.getMax().getZ()));
				drch = AABB(Vect3d(limites.getMin().getX(), coordenada, limites.getMin().getZ()), Vect3d(limites.getMax().getX(), limites.getMax().getY(), limites.getMax().getZ()));
				break;
			//Divisón por Z
			case 2:
				std::sort(puntos.begin(), puntos.end(), &compZ);
				coordenada = puntos[mitad].getZ();
				izq = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), limites.getMin().getZ()), Vect3d(limites.getMax().getX(), limites.getMax().getY(), coordenada));
				drch = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), coordenada), Vect3d(limites.getMax().getX(), limites.getMax().getY(), limites.getMax().getZ()));
				break;
		}
		
		std::vector<Vect3d> l1, l2;
		std::copy(puntos.begin(), puntos.begin() + mitad + 1, back_inserter(l1));
		std::copy(puntos.begin() + mitad + 1, puntos.end(), back_inserter(l2));

		Plane p = determinarPlanoDiv(nivel, coordenada, limites);

		planos.push_back(p);

		Nodo3dIzq = construir3DTree(l1, nivel + 1, izq);
		Nodo3dDrch = construir3DTree(l2, nivel + 1, drch);
		return Nodo3d(nivel, Nodo3dIzq, Nodo3dDrch, p, coordenada);

	}
	else
		return Nodo3d(nivel, puntos[0]);

}

Nodo2d KDTree::construir2DTree(std::vector<Point> puntos, int nivel, AABB limites) {

	if (puntos.size() > 1) {

		Nodo2d nodoIzq, nodoDrch;

		double coordenada;
		int mitad;

		if (puntos.size() % 2 == 0)
			mitad = puntos.size() / 2 - 1;
		else
			mitad = puntos.size() / 2;

		AABB izq;
		AABB drch;
		switch (nivel % 2) {
		//División por X
		case 0:
			std::sort(puntos.begin(), puntos.end(), &comp2X);
			coordenada = puntos[mitad].getX();
			izq = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), 0), Vect3d(coordenada, limites.getMax().getY(), 0));
			drch = AABB(Vect3d(coordenada, limites.getMin().getY(),0), Vect3d(limites.getMax().getX(), limites.getMax().getY(),0));
			break;
			//Divisón por Y
		case 1:
			std::sort(puntos.begin(), puntos.end(), &comp2Y);
			coordenada = puntos[mitad].getY();
			izq = AABB(Vect3d(limites.getMin().getX(), limites.getMin().getY(), 0), Vect3d(limites.getMax().getX(), coordenada, 0));
			drch = AABB(Vect3d(limites.getMin().getX(), coordenada, 0), Vect3d(limites.getMax().getX(), limites.getMax().getY(), 0));
			break;
		}

		std::vector<Point> l1, l2;
		std::copy(puntos.begin(), puntos.begin() + mitad + 1, back_inserter(l1));
		std::copy(puntos.begin() + mitad + 1, puntos.end(), back_inserter(l2));

		SegmentLine s = determinarSegmentoDiv(nivel, coordenada, limites);
		segmentos.push_back(s);


		nodoIzq = construir2DTree(l1, nivel + 1, izq);
		nodoDrch = construir2DTree(l2, nivel + 1, drch);
		return Nodo2d(nivel, nodoIzq, nodoDrch, s, coordenada);

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

Plane KDTree::determinarPlanoDiv(int nivel, double coordenada, AABB limites) {

	int eje = nivel % 3;

	Vect3d v1, v2, v3, v4;

	if (eje == 0) {
		v1 = Vect3d(coordenada, limites.getMax().getY(), limites.getMax().getZ());
		v2 = Vect3d(coordenada, limites.getMax().getY(), limites.getMin().getZ());
		v3 = Vect3d(coordenada, limites.getMin().getY(), limites.getMin().getZ());
		v4 = Vect3d(coordenada, limites.getMin().getY(), limites.getMax().getZ());
	}
	else if(eje == 1) {
		v1 = Vect3d(limites.getMax().getX(), coordenada, limites.getMax().getZ());
		v2 = Vect3d(limites.getMin().getX(), coordenada, limites.getMax().getZ());
		v3 = Vect3d(limites.getMin().getX(), coordenada, limites.getMin().getZ());
		v4 = Vect3d(limites.getMax().getX(), coordenada, limites.getMin().getZ());
	}
	else {
		v1 = Vect3d(limites.getMax().getX(), limites.getMax().getY(), coordenada);
		v2 = Vect3d(limites.getMin().getX(), limites.getMax().getY(), coordenada);
		v3 = Vect3d(limites.getMin().getX(), limites.getMin().getY(), coordenada);
		v4 = Vect3d(limites.getMax().getX(), limites.getMin().getY(), coordenada);
	}

	

	return Plane(v1, v2, v3, v4, true);

}

SegmentLine KDTree::determinarSegmentoDiv(int nivel, double coordenada, AABB limites) {

	int eje = nivel % 2;
	Point v1, v2;

	v1 = Point((1 - eje) * coordenada + eje * limites.getMax().getX(), eje * coordenada + (1 - eje) * limites.getMax().getY());
	v2 = Point((1 - eje) * coordenada + eje * limites.getMin().getX(), eje * coordenada + (1 - eje) * limites.getMin().getY());

	return SegmentLine(v1,v2);
}


Nodo2d* KDTree::buscarPunto(Point p) {
	
	Nodo2d *actual = new Nodo2d(raiz2D);
	int nivel = 0;

	while (!actual->esHoja()) {
		switch (nivel % 2) {
			//División por X
		case 0:
			if (p.getX() <= actual->getDivisoria())
				actual = actual->getIzq();
			else
				actual = actual->getDrch();
			break;
			//Divisón por Y
		case 1:
			if (p.getY() <= actual->getDivisoria())
				actual = actual->getIzq();
			else
				actual = actual->getDrch();
			break;
		}

		nivel++;
	}

	if (actual->getPunto().equal(p))
		return actual;
	return nullptr;
}

Nodo3d* KDTree::buscarPunto(Vect3d p) {

	Nodo3d* actual = new Nodo3d(raiz3D);
	int nivel = 0;

	while (!actual->esHoja()) {
		switch (nivel % 3) {
			//División por X
		case 0:
			if (p.getX() <= actual->getDivisoria())
				actual = actual->getIzq();
			else
				actual = actual->getDrch();
			break;
			//Divisón por Y
		case 1:
			if (p.getY() <= actual->getDivisoria())
				actual = actual->getIzq();
			else
				actual = actual->getDrch();
			break;
		case 2:
			if (p.getZ() <= actual->getDivisoria())
				actual = actual->getIzq();
			else
				actual = actual->getDrch();
			break;
		}

		nivel++;
	}

	if (actual->getPunto() == p)
		return actual;
	return nullptr;
}