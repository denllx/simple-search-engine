#include "scene.h"
#include "screen.h"
#include <QDebug>

Scene::Scene(QWidget* parent) :QLabel(parent) {
	father = (Screen*)parent;//ָ����mainwindow��ָ�룬���ڴ�������
}
