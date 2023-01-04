#ifndef BUILDING_H
#define BUILDING_H
#include "structs.h"
#include "polygon.h"

class Building
{
public:
    Building() {};
    Building(Polygon p1,Polygon p2,Polygon p3,Polygon p4,Polygon p5);

    QVector<Polygon> polygons;

    Material mat;

};

class Road
{
public:
    Road() {};
    Road(Polygon road,QVector<Polygon> marks);

    Polygon road;
    QVector<Polygon> marks;

};

class BusStop
{
public:
    BusStop() {};
    BusStop(Polygon p1,Polygon p2);

    QVector<Polygon> polygons;

};

#endif // BUILDING_H
