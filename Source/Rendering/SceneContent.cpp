#include "stdafx.h"
#include "SceneContent.h"

#include "ChronoUtilities.h"
#include "InclDraw2D.h"
#include "InclGeom2D.h"
#include "InclGeom3D.h"
#include "InclDraw3D.h"
#include "PointCloud.h"
#include "RandomUtilities.h"




// ----------------------------- BUILD YOUR SCENARIO HERE -----------------------------------

void AlgGeom::SceneContent::buildScenario()
{
    int tam = 10;    

    std::vector<Vect3d> points;
    for (int i = 0; i < tam; i++) {
        Vect3d point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x),
            RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
        points.push_back(point);
    }

    PointCloud3d *nubeP = new PointCloud3d(points);
    this->addNewModel((new DrawPointCloud(*nubeP))->overrideModelName()->setPointColor(vec3(0,1,0))->setPointSize(8));


    KDTree* arbol3D = new KDTree(nubeP);

    planos = arbol3D->getPlanos();
    maxNivel = arbol3D->getMax();

    for (int i = 0; i <= maxNivel; i++) {
        colores.insert(std::pair(i, vec3(RandomUtilities::getUniformRandomColor())));
    }

    delete nubeP;
    delete arbol3D;

}

void AlgGeom::SceneContent::buildCamera(uint16_t width, uint16_t height)
{
    Camera* camera = new Camera(width, height, false);
    camera->setPosition(vec3(-10.0f, 10.0f, 10.0f));
    camera->setLookAt(vec3(.0f, .0f, 0.0f));
    camera->saveCamera();

    this->_camera.push_back(std::unique_ptr<Camera>(camera));
}


// ------------------------------------------------------------------------------------------


AlgGeom::SceneContent::SceneContent()
{
}

AlgGeom::SceneContent::~SceneContent()
{
	_camera.clear();
	_model.clear();
}

void AlgGeom::SceneContent::addNewCamera(ApplicationState* appState)
{
	_camera.push_back(std::unique_ptr<Camera>(new Camera(appState->_viewportSize.x, appState->_viewportSize.y, true)));
}

void AlgGeom::SceneContent::addNewModel(Model3D* model)
{	
	_model.push_back(std::unique_ptr<Model3D>(model));
}

AlgGeom::Model3D* AlgGeom::SceneContent::getModel(Model3D::Component* component)
{
	for (auto& model : _model)
	{
		if (model->belongsModel(component))
			return model.get();
	}

	return nullptr;
}

void AlgGeom::SceneContent::construirKDTree(bool entero) {

    if (planos.size() > 0) {
        construir3DTree(entero);
    }
    else {
        construir2DTree(entero);
    }


}

void AlgGeom::SceneContent::construir2DTree(bool entero) {

    if (entero) {
        for (int i = avance2D; i < segmentos.size(); i++) {
            vec3 color = colores.find(segmentos[avance2D].second)->second;
            this->addNewModel((new DrawSegment(segmentos[avance2D].first))->overrideModelName()->setLineColor(color));
            avance2D++;
        }
    }
    else {
        if (avance2D < segmentos.size()) {
            vec3 color = colores.find(segmentos[avance2D].second)->second;
            this->addNewModel((new DrawSegment(segmentos[avance2D].first))->overrideModelName()->setLineColor(color));
            avance2D++;
        }
        else
            std::cout << "Fin proceso 2DTree" << std::endl;
    }

}

void AlgGeom::SceneContent::construir3DTree(bool entero) {

    if (entero) {
        for (int i = avance3D; i < planos.size(); i++) {
            DrawPlane* plane = new DrawPlane();
            plane->dibujaPlanoKDTree(planos[avance3D].first);
            vec3 color = colores.find(planos[avance3D].second)->second;

            this->addNewModel((plane)->overrideModelName()->setTriangleColor(vec4(color, 1)));
            avance3D++;
        }
    }
    else {
        if (avance3D < planos.size()) {
            DrawPlane* plane = new DrawPlane();
            plane->dibujaPlanoKDTree(planos[avance3D].first);
            vec3 color = colores.find(planos[avance3D].second)->second;

            this->addNewModel((plane)->overrideModelName()->setTriangleColor(vec4(color, 1)));
            avance3D++;

        }
        else
            std::cout << "Fin proceso 3DTree" << std::endl;
    }


}

void AlgGeom::SceneContent::randomizarNube2D(int tam) {

    this->_camera[0]->setPosition(vec3(.0f, .0f, 4.0f));

    avance2D = 0;

    this->planos.clear();

    this->_model.clear();

    this->colores.clear();

    PointCloud* nubeP2 = new PointCloud(tam, maxBoundaries.x, maxBoundaries.y);

    this->addNewModel((new DrawPointCloud(*nubeP2))->overrideModelName()->setPointColor(vec3(1, 0, 0))->setPointSize(8));

    KDTree* arbol2D = new KDTree(nubeP2);

    segmentos = arbol2D->getSegmentos();

    maxNivel = arbol2D->getMax();

    for (int i = 0; i <= maxNivel; i++) {
        vec3 color = RandomUtilities::getUniformRandomColor();
        colores.insert(std::pair(i, color));
    }

    delete nubeP2;
    delete arbol2D;
}

void AlgGeom::SceneContent::randomizarNube3D(int tam) {

    this->_camera[0]->setPosition(vec3(-10.0f, 10.0f, 10.0f));

    avance3D = 0;

    this->segmentos.clear();

    this->_model.clear();

    this->colores.clear();

    std::vector<Vect3d> points;
    for (int i = 0; i < tam; i++) {
        Vect3d point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x),
            RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
        points.push_back(point);
    }

    PointCloud3d* nubeP = new PointCloud3d(points);
    this->addNewModel((new DrawPointCloud(*nubeP))->overrideModelName()->setPointColor(vec3(0, 1, 0))->setPointSize(8));

    KDTree* arbol3D = new KDTree(nubeP);

    planos = arbol3D->getPlanos();

    maxNivel = arbol3D->getMax();

    for (int i = 0; i <= maxNivel; i++) {
        vec3 color = RandomUtilities::getUniformRandomColor();
        colores.insert(std::pair(i, color));
    }


    delete arbol3D;
    delete nubeP;
}
