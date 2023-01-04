#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QGraphicsView>
#include "structs.h"
#include "polygon.h"
#include "objects.h"

class Scene
{
public:
    Scene(QGraphicsView *gv);

    QGraphicsScene *scene;
    QGraphicsView *view;

    int height;
    int width;

    QVector<Polygon> polygons;

    QVector<Building> buildings;
    QVector<Road> roads;
    QVector<BusStop> stops;

    Camera camera;
    Point light;


    void clear_scene();
    void draw_line(Point *p1, Point *p2);
    void draw_point(int x, int y, QColor color);

    void draw_scene(Camera cam);

    void draw_polygon(Polygon *p);
    void ray_tracing(Camera cam);

    QColor ray_cast(Vec &orig, Vec &dir);
    bool scene_intersect(Vec &orig, Vec &dir,Vec &hit, Vec &n, Material &material, bool shadow = false);

    void operator=(Scene *scene1);

    void add_house(Point first, Point second, Material mat);
    void add_road(Point first, Point second, Material mat, bool car);
    void add_busstop(Point first, Point second, Material mat);
};

#endif // SCENE_H
