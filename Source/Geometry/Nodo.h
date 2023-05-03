#pragma once
#include "Plane.h"


class Nodo
{
	private:

		int nivel;
		Nodo *izq, *drch;
		Plane planoDivisorio;

		bool hoja;
		Vect3d punto3D;

	public:
		/**
		*	@brief Default constructor.
		*/
		Nodo();

		/**
		*	@brief Constructor.
		*/
		Nodo(int anivel, Nodo ni, Nodo nd, Plane planoDivision);

		Nodo(int anivel, Vect3d punto);

		/**
		*	@brief Copy constructor,
		*/
		Nodo(const Nodo& nodo);

		/**
		*	@brief Destructor.
		*/
		virtual ~Nodo();

		int getNivel() { return nivel; };
		Nodo* getDrch() { return drch; };
		Nodo* getIzq() { return izq; };
		Plane getPlane() { return planoDivisorio; };
		Vect3d getPunto() { if (hoja) return punto3D; else throw("error"); }

		void asignarPunto(Vect3d punto);
		void asignarIzq(Nodo nodoIzq);
		void asignarDrch(Nodo nodoDrch);
};

