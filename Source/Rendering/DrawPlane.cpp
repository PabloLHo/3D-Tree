#include "stdafx.h"
#include "DrawPlane.h"

AlgGeom::DrawPlane::DrawPlane() {

}

AlgGeom::DrawPlane::DrawPlane(Plane& plane) : Model3D(), _plane(plane) 
{
    size_t numVertices = 6;
    std::vector<Vect3d> vertices;
    Component* component = new Component;
    Vect3d punto(0, 0, - plane.getD() / plane.getC());
    Vect3d punto2(0, plane.getB(), (- plane.getD() - plane.getB()) / plane.getC());
    Vect3d punto3(0, -plane.getD() / plane.getB(), 0);
    Line3d* recta = new Line3d(punto, punto2);
    Line3d* recta_2 = new Line3d(punto, punto3);
    Line3d* recta_3 = new Line3d(punto2, punto3);
    
    vertices.push_back(recta->getPoint(10));
    vertices.push_back(recta_2->getPoint(10));
    vertices.push_back(recta_3->getPoint(10));
    vertices.push_back(recta->getPoint(-10));
    vertices.push_back(recta_2->getPoint(-10));
    vertices.push_back(recta_3->getPoint(-10));

    for (unsigned vertexIdx = 0; vertexIdx < numVertices; vertexIdx++) {

        Vect3d point = vertices[vertexIdx];

        component->_vertices.push_back(VAO::Vertex{ vec3(point.getX(), point.getY(), point.getZ()) });
        component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { vertexIdx, static_cast<unsigned int>((vertexIdx + 1) % numVertices), RESTART_PRIMITIVE_INDEX });
    }

    this->_components.push_back(std::unique_ptr<Component>(component));
    this->buildVao(component);
}

void AlgGeom::DrawPlane::dibujaPlanoKDTree(Plane& plane)
{
    size_t numVertices = 4;
    std::vector<Vect3d> vertices;
    Component* component = new Component;

    vertices.push_back(Vect3d(plane.getP1()));
    vertices.push_back(Vect3d(plane.getP2()));
    vertices.push_back(Vect3d(plane.getP3()));
    vertices.push_back(Vect3d(plane.getP4()));

    for (unsigned vertexIdx = 0; vertexIdx < numVertices; vertexIdx++) {

        Vect3d point = vertices[vertexIdx];
        component->_vertices.push_back(VAO::Vertex{ vec3(point.getX(), point.getY(), point.getZ())});

    }

    component->_indices[VAO::IBO_TRIANGLE].insert(component->_indices[VAO::IBO_TRIANGLE].end(), { 0,1,3, RESTART_PRIMITIVE_INDEX, 1,2,3, RESTART_PRIMITIVE_INDEX });

    this->_components.push_back(std::unique_ptr<Component>(component));
    this->buildVao(component);
}

AlgGeom::DrawPlane::~DrawPlane()
{
}

