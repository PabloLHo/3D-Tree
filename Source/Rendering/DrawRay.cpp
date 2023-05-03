#include "stdafx.h"
#include "DrawRay.h"

// Public methods

AlgGeom::DrawRay::DrawRay (RayLine &ray): Model3D(){
    Component* component = new Component;
    Point destino = ray.getPoint(1000);
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(ray.getA().getX(), ray.getA().getY(), .0f)},
            VAO::Vertex { vec3(destino.getX(), destino.getY(), .0f)}
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}

AlgGeom::DrawRay::DrawRay(Ray3d &ray) : Model3D() {

    Vect3d destino = ray.getPoint(1000);
    Component* component = new Component;
    component->_vertices.insert(component->_vertices.end(), {
            VAO::Vertex { vec3(ray.getOrigin().getX(), ray.getOrigin().getY(), ray.getOrigin().getZ())},
            VAO::Vertex { vec3(destino.getX(), destino.getY(), destino.getZ()) }
        });

    component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { 0, 1 });
    this->_components.push_back(std::unique_ptr<Component>(component));

    component->completeTopology();
    this->buildVao(component);
}