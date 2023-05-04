#pragma once
#include "SegmentLine.h"


class Nodo2d
{

	private:

		int nivel;
		Nodo2d* izq, * drch;
		SegmentLine lineaDivisoria;
		double coordenadaDivisoria;

		bool hoja;
		Point punto;

	public:
		/**
		*	@brief Default constructor.
		*/
		Nodo2d();

		/**
		*	@brief Constructor.
		*/
		Nodo2d(int anivel, Nodo2d ni, Nodo2d nd, SegmentLine lineaDivision, double coordenadaDivisoria);

		Nodo2d(int anivel, Point punto);

		/**
		*	@brief Copy constructor,
		*/
		Nodo2d(const Nodo2d& Nodo2d);

		/**
		*	@brief Destructor.
		*/
		virtual ~Nodo2d();

		int getNivel() { return nivel; };
		double getDivisoria() { return coordenadaDivisoria; };
		Nodo2d* getDrch() { return drch; };
		Nodo2d* getIzq() { return izq; };
		SegmentLine getSegmento() { return lineaDivisoria; };
		Point getPunto() { if (hoja) return punto; else throw("error"); }

		bool esHoja() { return hoja; };

		void asignarPunto(Point punto);
		void asignarIzq(Nodo2d Nodo2dIzq);
		void asignarDrch(Nodo2d Nodo2dDrch);
};

