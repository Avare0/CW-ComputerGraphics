#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structs.h"
#include <iostream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(ui->graphicsView);

    int rows = 0;

    ui->tableWidget_2->insertRow(0);
    ui->tableWidget_2->setItem(0,0, new QTableWidgetItem(
                                   QString::number(350) + ", " + QString::number(200) + ", " +QString::number(0)
                                   ));
    ui->tableWidget_2->setItem(0,1, new QTableWidgetItem(
                                   QString::number(410) + ", " + QString::number(400) + ", " +QString::number(20)
                                   ));
    ui->tableWidget_2->setItem(0,2, new QTableWidgetItem(
                                   "Серый"
                                   ));

    ui->tableWidget_3->insertRow(rows);
    qDebug() << rows;
    ui->tableWidget_3->setItem(rows,0, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,1, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,2, new QTableWidgetItem(
                                   true
                                   ));
    rows += 1;
    ui->tableWidget_3->insertRow(rows);
    qDebug() << rows;
    ui->tableWidget_3->setItem(rows,0, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,1, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,2, new QTableWidgetItem(
                                   true
                                   ));
    rows += 1;
    ui->tableWidget_3->insertRow(rows);
    qDebug() << rows;
    ui->tableWidget_3->setItem(rows,0, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,1, new QTableWidgetItem(
                                   QString::number(0)
                                   ));
    ui->tableWidget_3->setItem(rows,2, new QTableWidgetItem(
                                   true
                                   ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotate_camera() {

}

void MainWindow::on_pushButton_clicked()
{
    scene->draw_scene(camera);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {


    if (event->key() == Qt::Key_D) {
        camera.angle_v = 30;
        camera.angle_h = 0;
    } else if (event->key() == Qt::Key_A) {
        camera.angle_v = -30;
        camera.angle_h = 0;
    }
    else if (event->key() == Qt::Key_W) {
        camera.angle_h = 30;
        camera.angle_v = 0;
    }
    else if (event->key() == Qt::Key_S) {
        camera.angle_h = -30;
        camera.angle_v = 0;
    }
    scene->draw_scene(camera);
}

Vec get_color(QString color) {
    if (color == "Красный")
        return Vec(1,0,0);
    else if (color == "Синий")
        return Vec(0,0,1);
    else if (color == "Зеленый")
        return Vec(0,0.8,0);
    else if (color == "Фиолетовый")
        return Vec(0.8, 0, 0.8);
    else if (color == "Розовый")
        return Vec(1, 0.3, 0.6);
    else
        return Vec(-1,-1,-1);
}

void MainWindow::on_pushButton_2_clicked()
{
    bool err1,err2,err3 = false;
    double x1 = ui->lineEdit->text().toDouble(&err1);
    double y1 = ui->lineEdit_3->text().toDouble(&err2);
    double z1 = 0;
//    if (err1||err2||err3) error
    double x2 = ui->lineEdit_2->text().toDouble(&err1);
    double y2 = ui->lineEdit_4->text().toDouble(&err2);
    double z2 = ui->lineEdit_6->text().toDouble(&err3);
    //    if (err1||err2||err3) error
    QString color = ui->comboBox->currentText();
    Vec col = get_color(color);
//    if (col.x == -1) ERROR

    Point first = Point(
                x1,y1,z1
                );
    Point second = Point(x2,y2,z2);

    int rows = ui->tableWidget_2->rowCount();

    ui->tableWidget_2->insertRow(rows);
    qDebug() << rows;
    ui->tableWidget_2->setItem(rows,0, new QTableWidgetItem(
                                   QString::number(x1) + ", " + QString::number(y1) + ", " +QString::number(z1)
                                   ));
    ui->tableWidget_2->setItem(rows,1, new QTableWidgetItem(
                                   QString::number(x2) + ", " + QString::number(y2) + ", " +QString::number(z2)
                                   ));
    ui->tableWidget_2->setItem(rows,2, new QTableWidgetItem(
                                   color
                                   ));

    scene->add_house(first, second, col);

    scene->draw_scene(camera);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool err;
    double num = ui->lineEdit_7->text().toDouble(&err);
//    if err ERROR
//    if out of range error
    scene->buildings.removeAt(num - 1);
    ui->tableWidget_2->removeRow(num - 1);
    scene->draw_scene(camera);

}


void MainWindow::on_pushButton_4_clicked()
{
    bool err1,err2,err3 = false;

    double x1 = ui->lineEdit_12->text().toDouble(&err1);
    double y1 = ui->lineEdit_9->text().toDouble(&err2);
    double z1 = 0;
//    if (err1||err2||err3) error
    double x2 = ui->lineEdit_13->text().toDouble(&err1);
    double y2 = ui->lineEdit_10->text().toDouble(&err2);
    double z2 = 0;
    //    if (err1||err2||err3) error
    QString type = ui->comboBox_2->currentText();
    bool car = type == "Автомобильная"? true: false;

    Point first = Point(
                x1,y1,z1
                );
    Point second = Point(x2,y2,z2);

    int rows = ui->tableWidget_3->rowCount();

    ui->tableWidget_3->insertRow(rows);
    qDebug() << rows;
    ui->tableWidget_3->setItem(rows,0, new QTableWidgetItem(
                                   QString::number(x1) + ", " + QString::number(y1)
                                   ));
    ui->tableWidget_3->setItem(rows,1, new QTableWidgetItem(
                                   QString::number(x2) + ", " + QString::number(y2)
                                   ));
    ui->tableWidget_3->setItem(rows,2, new QTableWidgetItem(
                                   type
                                   ));

    scene->add_road(first, second, Material(Vec(0.5,0.5, 0.5)), car);

    scene->draw_scene(camera);
}

void MainWindow::on_pushButton_5_clicked()
{
    bool err;
    double num = ui->lineEdit_8->text().toDouble(&err);
//    if err ERROR
//    if out of range error
    scene->roads.removeAt(num - 1);
    ui->tableWidget_3->removeRow(num - 1);
    scene->draw_scene(camera);
}
