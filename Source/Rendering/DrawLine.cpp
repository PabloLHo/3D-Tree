#include "stdafx.h"
#include "DrawLine.h"

// Public methods

AlgGeom::DrawLine::DrawLine (Line &line): Model3D(){
    Component* component = new Component;
    Point origen = line.getPoint(1000);
    Point destino = line.getPoint(-1000);
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(origen.getX(), origen.getY(), .0f) },
            VAO::Vertex { vec3(destino.getX(), destino.getY(), .0f)}
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}

AlgGeom::DrawLine::DrawLine(Line3d& line) : Model3D(){

    Component* component = new Component;
    Vect3d origen = line.getPoint(1000);
    Vect3d destino = line.getPoint(-1000);
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(origen.getX(), origen.getY(), origen.getZ()) },
            VAO::Vertex { vec3(destino.getX(), destino.getY(), destino.getZ())}
    });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}