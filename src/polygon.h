#ifndef POLYGON_H
#define POLYGON_H
#include "structs.h"
#include <QGraphicsView>
#include "camera.h"
class Polygon
{
public:
    Polygon() {};
    Polygon(Point *p1,Point *p2,Point *p3,Point *p4, Material mat);
    Polygon(Point p1,Point p2,Point p3,Point p4, Material mat);

    QVector<Point> points_real;
    QVector<Point> points_transformed;

    QColor color;
    Material material;

    void rotate_polygon(Camera cam);

    void turn_x(Camera cam);
    void turn_y(Camera cam);
    void turn_z(Camera cam);

    void turn_light_y(Camera cam);
    void turn_light_z(Camera cam);

    double size_x();
    double size_y();

    double ray_intersect(Vec orig, Vec dir, Vec &norm);


};

#endif // POLYGON_H
