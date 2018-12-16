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
	//ui.pushButton->setText("hello world!");
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(changeText()));
	QTimer::singleShot(10, this, SLOT(startExtract()));
}

//有多少个文件已经被解析
void Screen::handleProcessed(int value) {
	if (value == -1) {//解析完成
		//确定总词数
		totalWords = tree->size();
		//打印id2title
		/*
		for (int i = 0; i < ID2title.size(); i++) {
			QString str=QString::fromLocal8Bit(ID2title[i].c_str());
			qDebug() <<"qdebug:"<<str << "\n";
		}*/
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
	/*for (int i = 0, len = ret.size(); i < len; i++) {
		cout << ret[i].first << ' ' << ret[i].second << endl;
		cout << ID2title[ret[i].first] << endl;
	}*/
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
}

//切换到跳转界面
void Screen::jumpToPage(QString str) {
	currentPage = str;
	scene->deleteLater();
	scene = new PageScene(this);
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