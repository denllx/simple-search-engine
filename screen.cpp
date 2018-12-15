#include <QTimer>
#include <QDebug>
#include <iostream>
#include "screen.h"
#include "scene.h"
#include "extractor.h"
#include "query.h"
/*void Screen::changeText() {
	ui.label->setText("clicked!");
}*/

Screen::Screen(QWidget* parent):
	QDialog(parent),
	ui(new Ui::Dialog)
	{
	ui->setupUi(this);
	//ui.pushButton->setText("hello world!");
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(changeText()));
	QTimer::singleShot(10, this, SLOT(startExtract()));
}

//有多少个文件已经被解析
void Screen::handleProcessed(int value) {
	if (value == -1) {//解析完成
		//return;
		//显示输入场景
		scene = new InputScene(this);
		//用户点击确认后，接收来自场景的字符串并分词
		connect(scene, SIGNAL(confirmed(char*)), this, SLOT(splitWords(char*)));
	}
	ui->progressBar->setValue(value);
	//progressBar->setValue(value);
}

void Screen::splitWords(char* sent) {
	CharStringLink words;
	getInput(sent, words);
	StringNode* p = words.head;
	while (p) {
		cout << p->str.c_str() << endl;
		p = p->next;
	}
	
}

void Screen::startExtract()//开始解析文件的进程
{
	Extractor* extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
}

Screen::~Screen() {
	delete ui;
}