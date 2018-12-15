#include "scene.h"
#include <QDebug>
#include <QTextCodec>

Scene::Scene(QWidget* parent) :QLabel(parent) {
	father = (Screen*)parent;//ָ����mainwindow��ָ�룬���ڴ�������
}

InputScene::InputScene(QWidget* parent) : 
	Scene(parent),
	ui(new Ui::Form) {
	ui->setupUi(this);
	//this->setGeometry(0, 0, 800, 600);
	//this->setStyleSheet("background-color:#FFFFFF");//����ɫΪ��ɫ
	//button = new QPushButton(this);
	//button->setText("hello input");
	//button->setGeometry(20, 20, 50, 50);
	//button->show();
	connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeWords(const QString&)));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendWords()));
	this->show();
}

void InputScene::sendWords() {
	//��wordsת��Ϊ��char*��ʽ�����͸�������
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	char* ret;
	QByteArray tmp = words.toLocal8Bit();
	ret = tmp.data();
	confirmed(ret);
}

void InputScene::changeWords(const QString& text) {//�û����뷢���仯
	words = text;
}

InputScene::~InputScene() {

}