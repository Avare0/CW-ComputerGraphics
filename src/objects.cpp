#include "objects.h"

Building::Building(Polygon p1,Polygon p2,Polygon p3,Polygon p4,Polygon p5)
{
    polygons.push_back(p1);
    polygons.push_back(p2);
    polygons.push_back(p3);
    polygons.push_back(p4);
    polygons.push_back(p5);
}

Road::Road(Polygon road, QVector<Polygon> marks)
{
    this->road = road;
    this->marks = marks;
}

BusStop::BusStop(Polygon p1,Polygon p2)
{
    polygons.push_back(p1);
    polygons.push_back(p2);
}
