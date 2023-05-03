#include "stdafx.h"
#include "Circle.h"

// Public methods

Circle::~Circle()
{
}

bool Circle::isInside(const Point &p)
{ 

    if (this->_center.distance(const_cast<Point&>(p)) <= this->_radius) {
        return true;
    }
    return false;

}

Polygon Circle::getPointsCircle(uint32_t numSubdivisions)
{        
    Polygon polygon;
    float angle = .0f, alpha = 2.0f * glm::pi<float>() / numSubdivisions;

    while (angle < (2.0f * glm::pi<float>() + glm::epsilon<float>()))
    {
        Point point = Point(std::cos(angle), -std::sin(angle));
        polygon.add(point);
        angle += alpha;
    }

    return polygon;
}

Circle& Circle::operator=(const Circle& circle)
{
    if (this != &circle)
    {
        this->_center = circle._center;
        this->_radius = circle._radius;
    }

    return *this;
}

Point Circle::getCentral() {
    return this->_center;
}

double Circle::getRadio() {
    return this->_radius;
}

RelationCircles Circle::relacionaCir(Circle& c) {
    Point* p = new Point(c.getCentral().getX(), c.getCentral().getY());
    double distancia = this->getCentral().distance(*p);
    float r1, r2;
    if (this->getRadio() > c.getRadio()) {
        r1 = this->getRadio();
        r2 = c.getRadio();
    }
    else {
        r2 = this->getRadio();
        r1 = c.getRadio();
    }
    if (BasicGeometry::equal(distancia, 0.0)) {
        return RelationCircles::CONCENTRIC;
    }
    else if ((r1 - r2) < distancia && distancia < (c.getRadio() + this->getRadio())) {
        return RelationCircles::SECANT;
    }else if(distancia > (c.getRadio() + this->getRadio())){
        return RelationCircles::EXTERNAL;
    }
    else if (distancia < (c.getRadio() + this->getRadio())) {
        return RelationCircles::INTERNAL;
    }
    else if (BasicGeometry::equal(distancia, (c.getRadio() + this->getRadio()))) {
        return RelationCircles::EXTERNAL_TANG;
    }
    else if (BasicGeometry::equal(distancia, (r1 - r2))) {
        return RelationCircles::INTERIOR_TANG;
    }

}

RelationCircleLine Circle::relacionaLine(Line& l) {
    Point* centro = new Point(this->getCentral().getX(), this->getCentral().getY());
    if (l.distancePointLine(*centro) < this->getRadio()) {
        return RelationCircleLine::INTERSECT;
    }
    else if (BasicGeometry::equal(this->getRadio(), l.distancePointLine(*centro))) {
        return RelationCircleLine::TANGENT;
    }
    return RelationCircleLine::NO_INTERSECT;
}

RelationCircleLine Circle::intersect(Line& line, Point& p1, Point& p2) {

    Vect2d* d = new Vect2d((line.getB() - line.getA()).getX(), (line.getB() - line.getA()).getY());

    Vect2d* var = new Vect2d((line.getA() - this->getCentral()).getX(), (line.getA() - this->getCentral()).getY());

    Point* circulo = new Point(this->getPointsCircle().getVertexAt(0).getX() * this->getRadio() + this->getCentral().getX(), this->getPointsCircle().getVertexAt(0).getY() * this->getRadio() + this->getCentral().getY());

    float r = std::pow((*circulo - this->getCentral()).getModule(), 2);
    float gamma = std::pow(d->dot(*var),2) - std::pow(d->getModule(),2) * (std::pow(var->getModule(),2) - r);
    if (BasicGeometry::equal(gamma, 0)) {
        gamma = 0;
    }
    float tmas = (-d->dot(*var) + sqrt(gamma)) / pow(d->getModule(), 2);
    float tmenos = (-d->dot(*var) - sqrt(gamma)) / pow(d->getModule(), 2);
    if (BasicGeometry::equal(gamma,0)) {
        p1 = line.getPoint(tmas);
        return RelationCircleLine::TANGENT;
    }
    else if (gamma > 0) {
        p1 = line.getPoint(tmas);
        p2 = line.getPoint(tmenos);
        return RelationCircleLine::INTERSECT;
    }
    return RelationCircleLine::NO_INTERSECT;
}

RelationCircleLine Circle::intersect(RayLine& rayLine, Point& p1, Point& p2) {

    Vect2d* d = new Vect2d((rayLine.getB() - rayLine.getA()).getX(), (rayLine.getB() - rayLine.getA()).getY());

    Vect2d* var = new Vect2d((rayLine.getA() - this->getCentral()).getX(), (rayLine.getA() - this->getCentral()).getY());

    Point* circulo = new Point(this->getPointsCircle().getVertexAt(0).getX() * this->getRadio() + this->getCentral().getX(), this->getPointsCircle().getVertexAt(0).getY() * this->getRadio() + this->getCentral().getY());

    float r = std::pow((*circulo- this->getCentral()).getModule(), 2);
    float gamma = std::pow(d->dot(*var), 2) - std::pow(d->getModule(), 2) * (std::pow(var->getModule(), 2) - r);

    if (BasicGeometry::equal(gamma, 0)) {
        gamma = 0;
    }

    float tmas = (-d->dot(*var) + sqrt(gamma)) / pow(d->getModule(), 2);
    float tmenos = (-d->dot(*var) - sqrt(gamma)) / pow(d->getModule(), 2);
    if (BasicGeometry::equal(gamma, 0)) {
        if (0 < tmas || BasicGeometry::equal(0.0, tmas)) {
            p1 = rayLine.getPoint(tmas);
            return RelationCircleLine::TANGENT;
        }
        return RelationCircleLine::NO_INTERSECT;
    }
    else if (gamma > 0) {
        if (0 < tmas || BasicGeometry::equal(0.0, tmas)) {
            p1 = rayLine.getPoint(tmas);
        }
        if (0 < tmenos || BasicGeometry::equal(0.0, tmenos)) {
            p2 = rayLine.getPoint(tmenos);
        }
        return RelationCircleLine::INTERSECT;
    }
    return RelationCircleLine::NO_INTERSECT;
}

RelationCircleLine Circle::intersect(SegmentLine& segment, Point& p1, Point& p2) {
    Vect2d* d = new Vect2d((segment.getB() - segment.getA()).getX(), (segment.getB() - segment.getA()).getY());

    Vect2d* var = new Vect2d((segment.getA() - this->getCentral()).getX(), (segment.getA() - this->getCentral()).getY());
    
    Point* circulo = new Point(this->getPointsCircle().getVertexAt(0).getX() * this->getRadio() + this->getCentral().getX(), this->getPointsCircle().getVertexAt(0).getY() * this->getRadio() + this->getCentral().getY());

    float r = std::pow((*circulo - this->getCentral()).getModule(), 2);
    float gamma = std::pow(d->dot(*var), 2) - std::pow(d->getModule(), 2) * (std::pow(var->getModule(), 2) - r);

    if (BasicGeometry::equal(gamma, 0)) {
        gamma = 0;
    }

    float tmas = (-d->dot(*var) + sqrt(gamma)) / pow(d->getModule(), 2);
    float tmenos = (-d->dot(*var) - sqrt(gamma)) / pow(d->getModule(), 2);

    if (BasicGeometry::equal(0.0, gamma)) {
        if ((0 < tmas && tmas < 1) || BasicGeometry::equal(0.0, tmas) || BasicGeometry::equal(1.0, tmas)) {
            p1 = segment.getPoint(tmas);
            return RelationCircleLine::TANGENT;
        }
        return RelationCircleLine::NO_INTERSECT;
    }
    else if (gamma > 0) {
        if ((0 < tmas && tmas < 1) || BasicGeometry::equal(0.0, tmas) || BasicGeometry::equal(1.0, tmas)) {
            p1 = segment.getPoint(tmas);
        }
        if ((0 < tmenos && tmenos < 1) || BasicGeometry::equal(0.0, tmenos) || BasicGeometry::equal(1.0, tmenos)) {
            p2 = segment.getPoint(tmenos);
        }
        return RelationCircleLine::INTERSECT;
    }
    return RelationCircleLine::NO_INTERSECT;

}
   