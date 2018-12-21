#include <QTextCodec>
#include "inputscene.h"

InputScene::InputScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Input) {
	ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeWords(const QString&)));
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendWords()));
	connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(sendWords()));//回车输入
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
	delete ui;
}
