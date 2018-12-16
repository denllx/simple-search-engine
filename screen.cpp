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

//�ж��ٸ��ļ��Ѿ�������
void Screen::handleProcessed(int value) {
	if (value == -1) {//�������
		//ȷ���ܴ���
		totalWords = tree->size();
		//��ӡid2title
		/*
		for (int i = 0; i < ID2title.size(); i++) {
			QString str=QString::fromLocal8Bit(ID2title[i].c_str());
			qDebug() <<"qdebug:"<<str << "\n";
		}*/
		//��ʾ���볡��
		scene = new InputScene(this);
		//�û����ȷ�Ϻ󣬽������Գ������ַ������ִ�
		connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
	}
	ui->progressBar->setValue(value);
	//progressBar->setValue(value);
}

void Screen::getArticleID(char* sent) {
	CharStringLink words;
	getInput(sent, words);	
	ret = query(tree, words);
	//��ret�е�����ID�����б����
	scene->deleteLater();
	scene = new ListScene(this);
	/*for (int i = 0, len = ret.size(); i < len; i++) {
		cout << ret[i].first << ' ' << ret[i].second << endl;
		cout << ID2title[ret[i].first] << endl;
	}*/
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
}

//�л�����ת����
void Screen::jumpToPage(QString str) {
	currentPage = str;
	scene->deleteLater();
	scene = new PageScene(this);
}
void Screen::startExtract()//��ʼ�����ļ��Ľ���
{
	Extractor* extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
}


Screen::~Screen() {
	delete ui;
}