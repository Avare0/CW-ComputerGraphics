#include "structs.h"

Point::Point(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}

Point* Point::copy()
{
    return new Point(x,y,z);
}

double deg_to_radi(double degrees)
{
    return degrees * M_PI / 180;
}

void Point::turn_y(Point rotatate_center, int angle_v)
{
    double tmp_z, tmp_x, cos_value, sin_value;
    cos_value = cos(deg_to_radi(angle_v));
    sin_value = sin(deg_to_radi(angle_v));
    tmp_x = x;
    tmp_z = z;
    x = rotatate_center.x + (tmp_x - rotatate_center.x)* cos_value - (tmp_z - rotatate_center.z) * sin_value;
    z = rotatate_center.z + (tmp_x - rotatate_center.x) * sin_value + (tmp_z - rotatate_center.z) * cos_value;
}

void Point::turn_x(Point rotatate_center, int angle_h)
{
    double tmp_y, tmp_z, cos_value, sin_value;
    cos_value = cos(deg_to_radi(angle_h));
    sin_value = sin(deg_to_radi(angle_h));

    tmp_y = y;
    tmp_z = z;
    y = rotatate_center.y + (tmp_y - rotatate_center.y) * cos_value + (tmp_z - rotatate_center.z) * sin_value;
    z = rotatate_center.z - (tmp_y - rotatate_center.y) * sin_value + (tmp_z - rotatate_center.z) * cos_value;
}

Point::Point()
{
    x = 0;
    y = 0;
    z = 0;
}

// ----------------VEC-------------------

Vec::Vec()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec::Vec(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}

Vec::Vec(Point &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

Vec::Vec(Camera cam)
{

    x = cam.center->x;
    y = cam.center->y;
    z = cam.center->z;
}


Vec Vec::operator-(Vec &two)
{
    return Vec(this->x - two.x,this->y - two.y, this->z - two.z );
}

double Vec::dot(Vec &two) {
    return this->x*two.x + this->y*two.y + this->z*two.z;
}
Vec Vec::operator*(double t) {
    return Vec(this->x * t, this->y * t, this->z * t);
}

Vec& Vec::normalize() {
    return *this = *this * (1/sqrt(x*x + y*y + z*z));
}

double Vec::norm() {
    return sqrt(x*x + y*y + z*z);
}

Vec Vec::operator+(Vec &two)
{
    return Vec(x + two.x, y + two.y, z + two.z);
}

//Vec Vec::operator=(Vec &b)
//{
//    *this = b;
//}

Vec Vec::operator-() {
    return Vec(-x, -y, -z);
}

Vec Vec::cross(Vec &two) {
    return Vec(this->y * two.z - this->z * two.y,
               this->z * two.x - this->x * two.z,
               this->x * two.y - this->y * two.x);
}

Material::Material(Vec three)
{
    diffuse_color = three;
}

Camera::Camera()
{
    center = new Point(250,250,350);
    rotatate_center = Point(250,250,0);
}

