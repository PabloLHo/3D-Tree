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

/* 
 *  File:   Circle.h
 *  Author: lidia
 *
 *  Created on 8 de febrero de 2021, 19:32
 */

#include "Point.h"
#include "Polygon.h"


enum RelationCircles {
    CONCENTRIC,
    EXTERNAL,
    INTERNAL,
    SECANT,
    INTERIOR_TANG,
    EXTERNAL_TANG
};

enum RelationCircleLine {
    INTERSECT,
    TANGENT,
    NO_INTERSECT
};

class Circle 
{
protected:
    Point       _center;             
    double      _radius;

public:
    /**
	*	@brief Default constructor. Coordinates are initialized with an invalid value.
	*/
    Circle (): _center(Point (0,0)), _radius(1.0) { }

    /**
    *	@brief Constructor.
	*/
    Circle(const Point &center, double radius): _center(center), _radius(radius) { }

    /**
	*	@brief Copy constructor.
	*/
    Circle (const Circle& orig): _center(orig._center), _radius(orig._radius) { }
    
	/**
	*	@brief Destructor.
	*/
    virtual ~Circle();

    /**
    *   @brief Checks if the point is inside the circle.
    *   @param p
    *   @return true if p is inside the circle 
    */  
    bool isInside (const Point &p);
    
    /**
    *   @return A polygon with circular shape.
    */
    Polygon getPointsCircle (uint32_t numSubdivisions = 256);

    /**
    *	@brief Assignment operator (override).
    */
    virtual Circle& operator=(const Circle& circle);

    /**
     *
     * @return punto central
     */
    Point getCentral();

    /**
     *
     * @return radio
     */
    double getRadio();


    RelationCircles relacionaCir(Circle& c);

    RelationCircleLine relacionaLine(Line& l);

    RelationCircleLine intersect(Line& line, Point& p1, Point& p2);
    RelationCircleLine intersect(RayLine& rayLine, Point& p1, Point& p2);
    RelationCircleLine intersect(SegmentLine& segment, Point& p1, Point& p2);
};

