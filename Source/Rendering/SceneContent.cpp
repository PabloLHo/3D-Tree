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
    vec3 minBoundaries = vec3(-3.0f, -.4, -3.0f), maxBoundaries = vec3(-minBoundaries);


    int tam = 10;
    //std::vector<Vect3d> points;
    //for (int i = 0; i < tam; i++) {
    //    Vect3d point(RandomUtilities::getUniformRandom(minBoundaries.x, maxBoundaries.x),
    //        RandomUtilities::getUniformRandom(minBoundaries.y, maxBoundaries.y), RandomUtilities::getUniformRandom(minBoundaries.z, maxBoundaries.z));
    //    points.push_back(point);
    //    std::cout << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")" << std::endl;
    //}

    //PointCloud3d *nubeP = new PointCloud3d(points);
    //this->addNewModel((new DrawPointCloud(*nubeP))->overrideModelName()->setPointColor(vec3(1,0,0)));


    //KDTree* arbol3D = new KDTree(nubeP);


    PointCloud* nubeP2 = new PointCloud(tam, maxBoundaries.x, maxBoundaries.y);
    for (int i = 0; i < tam; i++) {
        std::cout << "(" << nubeP2->getPoint(i).getX() << ", " << nubeP2->getPoint(i).getY() << ")" << std::endl;
    }
    this->addNewModel((new DrawPointCloud(*nubeP2))->overrideModelName()->setPointColor(vec3(1, 0, 0)));


    //PointCloud* nubeP2 = new PointCloud(tam, maxBoundaries.x, maxBoundaries.y);
    //this->addNewModel((new DrawPointCloud(*nubeP2))->overrideModelName()->setPointColor(vec3(1, 0, 0)));


    //KDTree* arbol2D = new KDTree(nubeP2);

    //std::vector<SegmentLine> segmentos = arbol2D->getSegmentos();

    //Representarlos directamente todos

    //for (int i = 0; i < segmentos.size(); i++) {
    //    this->addNewModel((new DrawSegment(segmentos[i]))->overrideModelName());
    //}

    //delete nubeP;

}

void AlgGeom::SceneContent::buildCamera(uint16_t width, uint16_t height)
{
    Camera* camera = new Camera(width, height, false);
    camera->setPosition(vec3(.0f, .0f, 4.0f));
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
