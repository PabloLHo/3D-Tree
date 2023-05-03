#pragma once
#include "PointCloud.h"
#include "PointCloud3d.h"




class KDTree{

	private:


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

};
