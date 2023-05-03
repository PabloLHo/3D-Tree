#pragma once
#include "Plane.h"


class Nodo3d
{
	private:

		int nivel;
		Nodo3d *izq, *drch;
		Plane planoDivisorio;
		double coordenadaDivisoria;

		bool hoja;
		Vect3d punto3D;

	public:
		/**
		*	@brief Default constructor.
		*/
		Nodo3d();

		/**
		*	@brief Constructor.
		*/
		Nodo3d(int anivel, Nodo3d ni, Nodo3d nd, Plane planoDivision, double coordenadaDivisoria);

		Nodo3d(int anivel, Vect3d punto);

		/**
		*	@brief Copy constructor,
		*/
		Nodo3d(const Nodo3d& Nodo3d);

		/**
		*	@brief Destructor.
		*/
		virtual ~Nodo3d();

		int getNivel() { return nivel; };
		Nodo3d* getDrch() { return drch; };
		Nodo3d* getIzq() { return izq; };
		Plane getPlane() { return planoDivisorio; };
		Vect3d getPunto() { if (hoja) return punto3D; else throw("error"); }

		void asignarPunto(Vect3d punto);
		void asignarIzq(Nodo3d Nodo3dIzq);
		void asignarDrch(Nodo3d Nodo3dDrch);
};

