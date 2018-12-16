#include <QTimer>
#include <QDebug>
#include <iostream>
#include "screen.h"
#include "scene.h"
#include "extractor.h"
#include "query.h"
#include "inputscene.h"
#include "listscene.h"
#include "pagescene.h"

/*void Screen::changeText() {
	ui.label->setText("clicked!");
}*/

Screen::Screen(QWidget* parent):
	QDialog(parent),
	ui(new Ui::Dialog)
	{
	ui->setupUi(this);
	QTimer::singleShot(10, this, SLOT(startExtract()));
}

//有多少个文件已经被解析
void Screen::handleProcessed(int value) {
	if (value == -1) {//解析完成
		//确定总词数
		totalWords = tree->size();
		//显示输入场景
		scene = new InputScene(this);
		//用户点击确认后，接收来自场景的字符串并分词
		connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
	}
	ui->progressBar->setValue(value);
	//progressBar->setValue(value);
}

void Screen::getArticleID(char* sent) {
	CharStringLink words;
	getInput(sent, words);	
	ret = query(tree, words);
	//将ret中的所有ID传给列表界面
	scene->deleteLater();
	scene = new ListScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
}

//切换到跳转界面
void Screen::jumpToPage(QString str) {
	currentPage = str;//xxx\\input\\0.html
	qDebug() << "currentpage=" << currentPage;
	//TODO 获从文件名获取文件的ID
	int end = str.lastIndexOf(".html");
	int start = str.lastIndexOf("\\");
	//数字在[start+1,end-1]
	QString numStr = str.mid(start + 1, end - 1 - start);
	QByteArray ba = numStr.toLatin1();
	char* cnum = ba.data();
	currentID=atoi(cnum);
	qDebug() << "current id=" << currentID << "\n";
	scene->deleteLater();
	scene = new PageScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToAnotherPage(QString)));
}

void Screen::jumpToAnotherPage(QString str) {
	qDebug() << "jump to another page:" << str << "\n";
	qDebug() << "currentid=" << currentID << "\n";
	scene->deleteLater();
	currentPage = str;
	scene = new PageScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToAnotherPage(QString)));
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