#include "scene.h"
#include "screen.h"
#include <QDebug>

Scene::Scene(QWidget* parent) :QLabel(parent) {
	father = (Screen*)parent;//指向父亲mainwindow的指针，用于传送数据
}
