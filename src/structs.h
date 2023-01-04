#ifndef POINT_H
#define POINT_H

#include <cmath>

#include <QMainWindow>



class Point
{
public:
    Point();
    Point(double x1, double y1, double z1);

    double x;
    double y;
    double z;

    Point* copy();
    void turn_x(Point rotatate_center, int angle_h);
    void turn_y(Point rotatate_center, int angle_v);
};


class Camera
{
public:
    Camera();

    Point *center;
    Point rotatate_center;

    int angle_h = 0;
    int angle_v = 0;
};


class Vec {
public:
    Vec();
    Vec(double x1, double y1, double z1);
    Vec(Point &p);
    Vec(Camera cam);

    double x;
    double y;
    double z;

    Vec operator-(Vec &two);
    Vec operator-();
    Vec operator*(double t);
    Vec operator+(Vec &b);
//    Vec operator=(Vec &b);


    Vec cross(Vec &two);
    double dot(Vec &two);
    Vec& normalize();
    double norm();
};

class Material {
public:
    Material() {};
    Material(Vec three);

    Vec diffuse_color;
};



#endif // POINT_H
