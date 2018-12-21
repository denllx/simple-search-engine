#include <QTextCodec>
#include "inputscene.h"

InputScene::InputScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Input) {
	ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeWords(const QString&)));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendWords()));
	connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendWords()));//�س�����
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
	delete ui;
}
