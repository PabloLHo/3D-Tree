#include "stdafx.h"
#include "DrawCircle.h"

// Public methods

AlgGeom::DrawCircle::DrawCircle(Circle& circle, uint32_t numSubdivisions, bool circulo): Model3D(), _circle(circle), _numSubdivisions(numSubdivisions)
{
    Polygon _polygon = circle.getPointsCircle(numSubdivisions);
    size_t numVertices = _polygon.getNumVertices();
    Component* component = new Component;
    if (circulo) {
        component->_vertices.push_back(VAO::Vertex{ vec3(circle.getCentral().getX() , circle.getCentral().getY(), .0f) });
        for (unsigned vertexIdx = 1; vertexIdx < _polygon.getNumVertices(); vertexIdx++) {

            Point point = _polygon.getVertexAt(vertexIdx - 1).getPoint();

            component->_vertices.push_back(VAO::Vertex{ vec3(point.getX() * circle.getRadio() + circle.getCentral().getX() , point.getY() * circle.getRadio() + circle.getCentral().getY(), .0f) });

            component->_indices[VAO::IBO_TRIANGLE].insert(component->_indices[VAO::IBO_TRIANGLE].end(), { 0, vertexIdx, static_cast<unsigned int>((vertexIdx + 1) % (numVertices + 1)), RESTART_PRIMITIVE_INDEX });

        }

        //último triangulo
        Point point = _polygon.getVertexAt(_polygon.getNumVertices() - 1).getPoint();
        component->_vertices.push_back(VAO::Vertex{ vec3(point.getX() * circle.getRadio() + circle.getCentral().getX() , point.getY() * circle.getRadio() + circle.getCentral().getY(), .0f) });
        component->_indices[VAO::IBO_TRIANGLE].insert(component->_indices[VAO::IBO_TRIANGLE].end(), { 0, static_cast<unsigned int>(_polygon.getNumVertices()), 1, RESTART_PRIMITIVE_INDEX });


        component->completeTopology();
        this->buildVao(component);
        this->_components.push_back(std::unique_ptr<Component>(component));
    }
    else {
        for (unsigned vertexIdx = 0; vertexIdx < _polygon.getNumVertices(); vertexIdx++) {

            Point point = _polygon.getVertexAt(vertexIdx).getPoint();

            component->_vertices.push_back(VAO::Vertex{ vec3(point.getX() * circle.getRadio() + circle.getCentral().getX() , point.getY() * circle.getRadio() + circle.getCentral().getY(), .0f) });
            component->_indices[VAO::IBO_LINE].insert(component->_indices[VAO::IBO_LINE].end(), { vertexIdx, static_cast<unsigned int>((vertexIdx + 1) % numVertices), RESTART_PRIMITIVE_INDEX });
        }

        this->_components.push_back(std::unique_ptr<Component>(component));
        this->buildVao(component);
    }
    
}
