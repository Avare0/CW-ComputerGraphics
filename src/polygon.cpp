#include "polygon.h"
#include <QDebug>

//Polygon::Polygon(Point *p1, Point *p2, Point *p3, Point *p4, Material mat)
//{
//    points_real.push_back(p1);
//    points_real.push_back(p2);
//    points_real.push_back(p3);
//    points_real.push_back(p4);
//    points_transformed.push_back(p1->copy());
//    points_transformed.push_back(p2->copy());
//    points_transformed.push_back(p3->copy());
//    points_transformed.push_back(p4->copy());
//    material = mat;
//}
Polygon::Polygon(Point p1, Point p2, Point p3, Point p4, Material mat)
{
    points_real.push_back(p1);
    points_real.push_back(p2);
    points_real.push_back(p3);
    points_real.push_back(p4);
    points_transformed.push_back(p1);
    points_transformed.push_back(p2);
    points_transformed.push_back(p3);
    points_transformed.push_back(p4);
    material = mat;
}

void Polygon::turn_x(Camera cam) {
    for(int i = 0; i < 4; i++)
        points_transformed[i].turn_x(cam.rotatate_center, cam.angle_h);
}
void Polygon::turn_y(Camera cam) {
    for(int i = 0; i < 4; i++)
        points_transformed[i].turn_y(cam.rotatate_center, cam.angle_v);

}

double Polygon::size_x()
{
    return fabs(points_real[0].x - points_real[3].x);
}
double Polygon::size_y()
{
    return fabs(points_real[0].y - points_real[2].y);
}

double triangle_intersect(Vec &orig, Vec &dir, Point &p1, Point &p2, Point &p3, Vec &norm) {
    Vec v0 = Vec(p1);
    Vec v1 = Vec(p2);
    Vec v2 = Vec(p3);

    Vec e1 = v1 - v0;
    Vec e2 = v2 - v0;

    double eps = 1e-2;

    Vec pvec = dir.cross(e2);
    norm = -e1.cross(e2);
    double det = e1.dot(pvec);


    if (det < eps && det > -eps) {
        return 0;
    }

    double inv_det = 1 / det;
    Vec tvec = orig - v0;
    double u = tvec.dot(pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }

    Vec qvec = tvec.cross(e1);
    double v = dir.dot(qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return 0;

    return e2.dot(qvec) * inv_det;
}

double Polygon::ray_intersect(Vec orig, Vec dir, Vec &norm) {
    double dist1 = triangle_intersect(orig, dir, points_transformed[0],points_transformed[1],points_transformed[2], norm);
    if (dist1 != 0)
        return dist1;
    double dist2 = triangle_intersect(orig, dir, points_transformed[2],points_transformed[3],points_transformed[0], norm);
    if (dist2 != 0)
        return dist2;
    return 0;
}

