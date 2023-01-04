#include "scene.h"
#include <iostream>
#include <qdebug.h>
#include <algorithm>
#include <QtMath>
#include <thread>

#define MARK 0.13
#define GROUND 0.1

Scene::Scene(QGraphicsView *gv)
{
    view = gv;
    scene =  new QGraphicsScene(view);
    view->setScene(scene);

    width = view->width();
    height = view->height();

//    Polygon a1 = Polygon(Point(100,100,0),
//                             Point(100,300,0),
//                             Point(300,300,100),
//                             Point(300,100,100),
//    Material(Vec(0.5, 1, 0.5)));
    Polygon a2 = Polygon(Point(0,0,0),
                             Point(0,1000,0),
                             Point(1000,1000,0),
                             Point(1000,0,0),
                              Material(Vec(0.5, 0.9, 1)));
    Polygon a3 = Polygon(Point(200,200,100),
                             Point(200,250,100),
                             Point(250,250,100),
                             Point(250,200,100),
                              Material(Vec(0.5, 0.9, 1)));

//    polygons.push_back(a1);
    polygons.push_back(a2);
//    polygons.push_back(a3);

    add_house(
             Point(350,200,0),
             Point(410,400,200),
             Material(Vec(0.5,0.5, 0.5))
                );
        add_road(
                 Point(50,50,0),
                 Point(400,100,0),
                 Material(Vec(0.5,0.5, 0.5)),
                    true
                    );
        add_road(
                 Point(200,0,0),
                 Point(300,400,0),
                 Material(Vec(0.5,0.5, 0.5)),
                    true
                    );
        add_road(
                 Point(450,0,0),
                 Point(550,400,0),
                 Material(Vec(0.5,0.5, 0.5)),
                    true
                    );
        add_busstop(
                    Point(100,100,0),
                    Point(150,120,20),
                    Material(Vec(0.5,0.5, 0.5))
                    );

    light.x = -100;
    light.y = -100;
    light.z = 250;
}

void Scene::clear_scene()
{
    delete scene;
    this->scene = new QGraphicsScene(view);
    view->setScene(scene);
}

void Scene::draw_line(Point *p1, Point *p2)
{
    scene->addLine(p1->x, p1->y, p2->x, p2->y);
}
void Scene::draw_point(int x, int y, QColor color)
{
    scene->addEllipse(x,y,1,1,color);
}

void Scene::draw_scene(Camera cam)
{
    clear_scene();
    for (Polygon &p: polygons) {
        p.turn_y(cam);
        p.turn_x(cam);
    }
    for (Building &b: buildings) {
        for(Polygon &p: b.polygons) {
            p.turn_y(cam);
            p.turn_x(cam);
        }
    }

    for (Road &r: roads) {
        r.road.turn_y(cam);
        r.road.turn_x(cam);
        for(Polygon &p: r.marks) {
            p.turn_y(cam);
            p.turn_x(cam);
        }
    }
    for (BusStop &r: stops) {
        for(Polygon &p: r.polygons) {
            p.turn_y(cam);
            p.turn_x(cam);
        }
}
    light.turn_y(camera.rotatate_center, cam.angle_v);
    light.turn_x(camera.rotatate_center, cam.angle_h);
    ray_tracing(cam);
}

//void Scene::draw_polygon(Polygon *p)
//{
//    draw_line(p->points_transformed[0], p->points_transformed[1]);
//    draw_line(p->points_transformed[1], p->points_transformed[2]);
//    draw_line(p->points_transformed[2], p->points_transformed[3]);
//    draw_line(p->points_transformed[3], p->points_transformed[0]);
//}

void Scene::operator=(Scene *scene1)
{
    view = scene1->view;
    scene = scene1->scene;
}

void Scene::add_house(Point first, Point second, Material mat)
{
    Point floor, ceil;
    if (first.z == 0){
        floor = first;
        ceil = second;
    } else if (second.z == 0) {
        floor = second;
        ceil = first;
    } // ELSE ERROR!!!!!!!!!!!!!

//    if (floor.x < 0 or floor.y < 0 or ceil.x < 0 or ceil.y < 0) ERROR

    Polygon one = Polygon(
                floor,
                Point(floor.x, ceil.y, floor.z),
                Point(floor.x, ceil.y, ceil.z),
                Point(floor.x, floor.y, ceil.z),
                mat
                );
    Polygon two = Polygon(
                Point(ceil.x, floor.y, floor.z),
                Point(ceil.x, ceil.y, floor.z),
                Point(ceil.x, ceil.y, ceil.z),
                Point(ceil.x, floor.y, ceil.z),
                mat
                );
    Polygon three = Polygon(
                Point(floor.x,ceil.y, floor.z),
                Point(floor.x,ceil.y, ceil.z),
                Point(ceil.x,ceil.y, ceil.z),
                Point(ceil.x,ceil.y, floor.z),
                mat
                );
    Polygon four = Polygon(
                floor,
                Point(floor.x,floor.y, ceil.z),
                Point(ceil.x,floor.y, ceil.z),
                Point(ceil.x,floor.y, floor.z),
                mat
                );
    Polygon five = Polygon(
                Point(floor.x, floor.y, ceil.z),
                Point(floor.x,ceil.y, ceil.z),
                Point(ceil.x,ceil.y, ceil.z),
                Point(ceil.x,floor.y, ceil.z),
                mat
                );

    buildings.push_back(Building(one, two, three,four,five));


//    polygons.push_back(one);
//    polygons.push_back(two);
//    polygons.push_back(three);
//    polygons.push_back(four);
//    polygons.push_back(five);
}

void Scene::add_road(Point first, Point second, Material mat, bool car) {

    QVector<Polygon> marks_tmp;

    Polygon road = Polygon(
                first,
                Point(first.x, second.y, GROUND),
                second,
                Point(second.x, first.y, GROUND),
                mat
                );
    if (car) {

    double size_x = road.size_x();
    double size_y = road.size_y();
    double length, width;

    bool flag_x = false;
    if (size_x > size_y) {
        flag_x = true;
        length = size_x;
        width = size_y;
    } else {
        length = size_y;
        width = size_x;
    }

    int mark_length = 40;
    int mark_width = 3;
    int interval = 20;
    int amount = length /  (interval + mark_length);

    if (flag_x) {
        for(int i = 0; i < amount + 1; i++)
        {
            double y = fabs(second.y - first.y) / 2;
            Polygon mark = Polygon(
                        Point(first.x + i*(mark_length + interval), first.y + y - mark_width, MARK),
                        Point(first.x + i*(mark_length + interval), first.y + y + mark_width, MARK),
                        Point(first.x + mark_length + i*(mark_length + interval), first.y + y + mark_width, MARK),
                        Point(first.x + mark_length + i*(mark_length + interval), first.y + y - mark_width, MARK),
                        Material(Vec(1,1,1))
                        );
            marks_tmp.push_back(mark);

        };
    } else {
        for(int i = 0; i < amount + 1; i++)
        {
            double x = fabs(second.x - first.x) / 2;
            Polygon mark = Polygon(
                        Point(first.x + x - mark_width,first.y + i*(mark_length + interval), MARK),
                        Point(first.x + x - mark_width,first.y + i*(mark_length + interval) + mark_length,MARK),
                        Point(first.x + x + mark_width,first.y + i*(mark_length + interval) + mark_length,MARK),
                        Point(first.x + x + mark_width,first.y + i*(mark_length + interval),MARK),
                        Material(Vec(1,1,1))
                        );
            marks_tmp.push_back(mark);

        };
    }
    }

    roads.push_back(Road(road, marks_tmp));
}

void Scene::add_busstop(Point first, Point second, Material mat) {
    //    if (first.z != 0 && second.z != 0) ERROR
    Point floor, ceil;
    if (first.z == 0){
        floor = first;
        ceil = second;
    } else if (second.z == 0) {
        floor = second;
        ceil = first;
    } // ELSE ERROR!!!!!!!!!!!!!

    Polygon wall = Polygon(
                floor,
                Point(floor.x, ceil.y, floor.z),
                Point(floor.x, ceil.y, ceil.z),
                Point(floor.x, floor.y, ceil.z),
                mat
                );
    Polygon roof = Polygon(
                Point(floor.x, floor.y, ceil.z),
                Point(floor.x, ceil.y, ceil.z),
                ceil,
                Point(ceil.x, floor.y, ceil.z),
                mat
                );

    stops.push_back(BusStop(wall, roof));
}



bool Scene::scene_intersect(Vec &orig, Vec &dir,Vec &hit, Vec &n, Material &material, bool shadow) {
    double max_dist = 100000000;
    double eps = 1e-3;

    for(Polygon &p: polygons) {
        double intersect = p.ray_intersect(orig, dir, n);

        if (fabs(intersect) > eps && intersect > 0 && intersect < max_dist) {

            max_dist = intersect;
            hit = dir*intersect + orig;
            material=p.material;
//            qDebug() << hit.x << hit.y << hit.z;
        }
    }

    for (Building &b: buildings) {
        for(Polygon &p: b.polygons) {
            double intersect = p.ray_intersect(orig, dir, n);

            if (fabs(intersect) > eps && intersect > 0 && intersect < max_dist) {

                max_dist = intersect;
                hit = dir*intersect + orig;
                material=p.material;
    //            qDebug() << hit.x << hit.y << hit.z;
            }
        }
    }

    for (BusStop &b: stops) {
        for(Polygon &p: b.polygons) {
            double intersect = p.ray_intersect(orig, dir, n);

            if (fabs(intersect) > eps && intersect > 0 && intersect < max_dist) {

                max_dist = intersect;
                hit = dir*intersect + orig;
                material=p.material;
    //            qDebug() << hit.x << hit.y << hit.z;
            }
        }
    }

    int count_roads_intersect = 0;
    Material road_mat;
    road_mat.diffuse_color=Vec(0,0,0);

    if (shadow == false) {

    for (Road &r: roads) {
        double intersect = r.road.ray_intersect(orig, dir, n);
        if (fabs(intersect) > eps && intersect > 0)
            count_roads_intersect += 1;
        if (fabs(intersect) > eps && intersect > 0 && intersect < max_dist) {
            max_dist = intersect;
            hit = dir*intersect + orig;
            material= r.road.material;
            road_mat = r.road.material;
//            qDebug() << hit.x << hit.y << hit.z;
        }
        for(Polygon &p: r.marks) {
            double intersect = p.ray_intersect(orig, dir, n);

            if (fabs(intersect) > eps && intersect > 0 && intersect < max_dist) {

                max_dist = intersect;
                hit = dir*intersect + orig;
                material=p.material;
    //            qDebug() << hit.x << hit.y << hit.z;
            }
        }
    }
    if (count_roads_intersect > 1)
        material = road_mat;
    }


    return max_dist < 100000;
}


QColor Scene::ray_cast(Vec &orig, Vec &dir) {
    Vec point, n;
    Material material;

    if (!scene_intersect(orig, dir,point, n, material))
        return QColor(250,250, 250); //gray

    Vec light_dir = (Vec(light) - point).normalize();
    double light_dist = (Vec(light) - point).norm();
    n = n.normalize();

    Vec shadow_orig = light_dir.dot(n) < 0 ? -n*1e-3 + point  : n*1e-3 + point;
    Vec shadow_pt, shadow_n;
    Material tmp;
//    qDebug() << "SHADOW-----START-------";
    if (scene_intersect(shadow_orig, light_dir, shadow_pt, shadow_n, tmp,true)
            && (shadow_pt - shadow_orig).norm() < light_dist){
//        qDebug() << "SHADOW-------END----------";
        return QColor(material.diffuse_color.x*255*0.1, material.diffuse_color.y*255*0.1, material.diffuse_color.z*255*0.1);
    }

    double light_intens = 1 * light_dir.dot(n);
//    double light_intens = 1;

    material = material.diffuse_color * light_intens;
    double max = std::max(material.diffuse_color.x, std::max(material.diffuse_color.y, material.diffuse_color.z));
    if (material.diffuse_color.x > 1 ||
            material.diffuse_color.y > 1 ||
            material.diffuse_color.z > 1)
        material.diffuse_color = material.diffuse_color*(1/max);

    return QColor(material.diffuse_color.x * 255, material.diffuse_color.y* 255, material.diffuse_color.z* 255);
}

void Scene::ray_tracing(Camera camera)
{
    const double fov = M_PI / 2.;
    Vec cam = Vec(camera);
    double x = 1;
    #pragma omp for
    for(int j = 0; j < height; j++)
        for(int i = 0; i < width; i++) {
            x =(2*(i)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            double y = -(2*(j)/(float)height - 1)*tan(fov/2.);
//            y = 2*(i+0.5)/width*tan(fov/2)*(fabs(cam.x - x));
//            double z = 2*i/height*tan(fov/2)*(fabs(cam.x - x));
//            qDebug() << y << z;
//            double dir_x =  (i + 0.5) -  width/2.;
//            double dir_y = -(j + 0.5) + height/2.;    // this flips the image at the same time
//            double dir_z = -height/(2.*tan(fov/2.));



            QColor color = ray_cast(cam, Vec(x,y, -1).normalize());

            draw_point(i,j, color);

//            draw_point();

        }
}



