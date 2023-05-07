#include "stdafx.h"
#include "PointCloud.h"
#include "RandomUtilities.h"

PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
	for (int i = 0; i < size; i++) {
		this->_points.push_back(Point(RandomUtilities::getUniformRandom(-max_x, max_x), RandomUtilities::getUniformRandom(-max_y, max_y)));
	}
}


PointCloud::PointCloud(std::vector<Point> puntos)
{
	this->_points = puntos;
}



PointCloud::PointCloud(const std::string& filename)
{
	std::ifstream infile(filename + ".bin", std::ifstream::binary);
	int numPuntos;
	infile.read((char*)&numPuntos, sizeof(int));
	std::vector<Point> puntos;
	for (int i = 0; i < numPuntos; i++) {
		Point punto;
		infile.read((char*)&punto, sizeof(Point));
		puntos.push_back(punto);
	}

	infile.close();

	this->_points = puntos;
}

PointCloud::~PointCloud()
{
}

void PointCloud::addPoint(const Point& p)
{
	_points.push_back(p);
}

Point PointCloud::centralPoint()
{
	std::vector<double> distancias;
	for (int i = 0; i < this->size(); i++)
		distancias.push_back(0);
	for (int i = 0; i < this->size() - 1; i++) {
		for (int x = i + 1; x < this->size(); x++) {
			double distancia = this->_points[i].distance(this->_points[x]);
			distancias[i] += distancia;
			distancias[x] += distancia;
		}
	}

	double minimo = FLT_MAX;
	int indice = 0;
	for (int i = 1; i < this->size(); i++)
		if (distancias[i] < minimo) {
			minimo = distancias[i];
			indice = i;
		}
    return this->_points[indice];
}

void PointCloud::deletePoint(int index)
{
	if (index < _points.size())
	{
		_points.erase(_points.begin() + index);
	}
}

void PointCloud::getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y)
{
}

Point PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) 
	{
		return _points[position];
	}

	return Point();
}

PointCloud & PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud)
	{
		this->_points = pointCloud._points;
	}

	return *this;
}

void PointCloud::save(const std::string& filename)
{
	std::ofstream outfile(filename + ".bin", std::ofstream::binary);
	int numPuntos = this->size();
	outfile.write((char*)&numPuntos, sizeof(int));
	outfile.write((char*)this->_points.data(), numPuntos * sizeof(Point));
	outfile.close();
}