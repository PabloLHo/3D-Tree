#pragma once
#include "PointCloud.h"
#include "PointCloud3d.h"
#include "Nodo.h"



class KDTree{

	private:

		Nodo raiz;

	public:
		/**
		*	@brief Default constructor.
		*/
		KDTree();

		/**
		*	@brief Constructor.
		*/
		KDTree(const PointCloud& nP);

		KDTree(const PointCloud3d& nP);

		/**
		*	@brief Copy constructor,
		*/
		KDTree(const KDTree& kdTree);

		/**
		*	@brief Destructor.
		*/
		virtual ~KDTree();

		Nodo construir3DTree(std::vector<Vect3d> puntos, int nivel);

		Nodo construir2DTree(std::vector<Point> puntos, int nivel);

};
