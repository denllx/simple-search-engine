#include "scene.h"
#include <QDebug>
#include <QTextCodec>

Scene::Scene(QWidget* parent) :QLabel(parent) {
	father = (Screen*)parent;//指向父亲mainwindow的指针，用于传送数据
}

InputScene::InputScene(QWidget* parent) : 
	Scene(parent),
	ui(new Ui::Form) {
	ui->setupUi(this);
	//this->setGeometry(0, 0, 800, 600);
	//this->setStyleSheet("background-color:#FFFFFF");//背景色为白色
	//button = new QPushButton(this);
	//button->setText("hello input");
	//button->setGeometry(20, 20, 50, 50);
	//button->show();
	connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeWords(const QString&)));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendWords()));
	this->show();
}

void InputScene::sendWords() {
	//将words转换为成char*形式并发送给主窗口
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	char* ret;
	QByteArray tmp = words.toLocal8Bit();
	ret = tmp.data();
	confirmed(ret);
}

void InputScene::changeWords(const QString& text) {//用户输入发生变化
	words = text;
}

InputScene::~InputScene() {

}