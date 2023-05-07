/*   Copyright (C) 2023 Lidia Ortega Alvarado, Alfonso Lopez Ruiz
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see https://github.com/AlfonsoLRz/AG2223.
*/

#pragma once

#include "stdafx.h"
#include "ApplicationState.h"
#include "Camera.h"
#include "Model3D.h"
#include "SegmentLine.h"
#include "Plane.h"

namespace AlgGeom
{
	class SceneContent
	{
	public:
		vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);
		std::vector<std::unique_ptr<Camera>>	_camera;
		std::vector<std::unique_ptr<Model3D>>	_model;

		int avance2D = 0;
		int avance3D = 0;
		std::vector<SegmentLine> segmentos;
		std::vector<Plane> planos;

		SceneContent();
		virtual ~SceneContent();

		void addNewCamera(ApplicationState* appState);
		void addNewModel(Model3D* model);
		void buildCamera(uint16_t width, uint16_t height);
		void buildScenario();
		Model3D* getModel(Model3D::Component* component);

		void construirKDTree(bool entero);

		void randomizarNube3D(int tam);
		void randomizarNube2D(int tam);

	protected:
		void construir2DTree(bool entero);
		void construir3DTree(bool entero);

	};
}