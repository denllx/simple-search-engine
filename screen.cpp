#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QCloseEvent>
#include "screen.h"
#include "scene.h"
#include "extractor.h"
#include "query.h"
#include "inputscene.h"
#include "listscene.h"
#include "pagescene.h"

Screen::Screen(QWidget* parent):
	QDialog(parent),
	ui(new Ui::Dialog)
	{
	ui->setupUi(this);
	QTimer::singleShot(10, this, SLOT(startExtract()));
}

//�ж��ٸ��ļ��Ѿ�������
void Screen::handleProcessed(int value) {
	if (value == -1) {//�������
		//ɾ���߳�
		extractor->quit();
		//ȷ���ܴ���
		totalWords = tree->size();
		//��ʾ���볡��
		scene = new InputScene(this);
		//�û����ȷ�Ϻ󣬽������Գ������ַ������ִ�
		connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
		denyClose = false;//֮�������û��رմ���
	}
	ui->progressBar->setValue(value);
}

//����������洫�����ַ���
//�ҵ������ؼ�����������ID�б�
void Screen::getArticleID(char* sent) {
	CharStringLink words;
	getInput(sent, words,dic,stop);	
	ret = query(tree, words);
	qDebug() << "recommanded list IDs";
	for (int i=0;i<ret.size();i++)
		qDebug() << ret[i];
	//��ret�е�����ID�����б����
	scene->deleteLater();
	scene = new ListScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
	connect(scene, SIGNAL(toInput()), this, SLOT(jumpToInput()));
}


//��xxx.info���ļ�������ȡID
int filename2id(const QString& str) {
	//����ļ�����ȡ�ļ���ID
	int end = str.lastIndexOf(".info");
	int start = str.lastIndexOf("\\");
	//������[start+1,end-1]
	QString numStr = str.mid(start + 1, end - 1 - start);
	QByteArray ba = numStr.toLatin1();
	char* cnum = ba.data();
	return atoi(cnum);
}

//���������Ӻ�����ҳ����ת�ź�
void Screen::jumpToPage(QString str) {
	qDebug() << "screen::jump to page";
	currentPage = str;//xxx\\output\\0.info
	pages.push(currentPage);
	currentID=filename2id(currentPage);
	IDs.push(currentID);
	//������ǵ�һ��ҳ�棬��ҳ�������һ��ҳ��ĵ���б�
	if (!clickedPagelinks.empty()) {
		qDebug() << "clickedpagelinks.size:" << clickedPagelinks.size();
		clickedPagelinks[clickedPagelinks.size() - 1].push_back(currentID);
	}
	clickedPagelinks.push_back(vector<int>(0));//��һ���µ�ҳ�棬��Ӧһ���յĵ���б�
	//�����Ƽ��б�
	currentRecommand = _recommand(currentID, sim, totalArticles, totalWords);
	qDebug() << "current recommand:" << endl;
	for (int i = 0; i < currentRecommand.size(); i++) cout << currentRecommand[i] << " ";
	cout << endl;
	recommands.push(currentRecommand);
	scene->deleteLater();
	scene = new PageScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
	connect(scene, SIGNAL(backPage()), this, SLOT(jumpToLastPage()));
}

//���������˰�ť��������ת�ź�
void Screen::jumpToLastPage() {
	qDebug() << "jump to to last page";
	
	if (IDs.size()>1) {//��ǰ���ǵ�һ����ҳ
		//ȡ����һҳ��ID,�ļ������Ƽ�ID�б�
		recommands.pop();
		IDs.pop();
		pages.pop();
		currentPage = pages.top();
		currentRecommand = recommands.top();
		currentID = IDs.top();
		clickedPagelinks.pop_back();
		scene->deleteLater();
		scene = new PageScene(this);
		connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
		connect(scene, SIGNAL(backPage()), this, SLOT(jumpToLastPage()));
	}
	else {//��һ������ҳ����ˣ������б�ҳ
		//��ȡ���һ�������������ID
		int lastID = IDs.top();
		IDs.pop();
		pages.pop();
		recommands.pop();
		currentPage = "";
		currentRecommand = vector<int>(0);
		currentID = -1;
		clickedPagelinks.pop_back();
		//�ҵ���һ�������������ҳ
		int i =0,len=ret.size();
		for (; i < len; i++) {
			if (ret[i].first == lastID) break;
		}
		if (i != len) {//�ҵ�����һ�������������ҳ
			clickedLinks.push_back(i);
			sort(clickedLinks.begin(), clickedLinks.end());
		}
		//�����б�ҳ
		scene->deleteLater();
		qDebug() << "clicked linkgs:";
		for (int i = 0; i < clickedLinks.size(); i++) qDebug() << clickedLinks[i] << " ";
		scene = new ListScene(this);
		connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
		connect(scene, SIGNAL(toInput()), this, SLOT(jumpToInput()));
	}
}

//������б���洫���Ļص�����������ź�
void Screen::jumpToInput() {
	qDebug() << "jump to input";
	//���������ʷ
	ret.clear();
	clickedLinks.clear();
	clickedPagelinks.clear();
	currentPage = "";
	currentID = -1;
	IDs.clear();
	currentRecommand.clear();
	recommands.clear();
	//������������
	qDebug() << "build input scene";
	scene->deleteLater();
	scene = new InputScene(this);
	connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
}

void Screen::startExtract()//��ʼ�����ļ��Ľ���
{
	extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
	//���ô���Ϊ���ɹرգ���ֹ�����߳�����ʱ�жϴ���
	//setwindowFlags(QT::window | Qt::Framelesswindowhint | QT::windowTitlehint)
	//setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowTitleHint);	
}

//��ֹ�رմ���
void Screen::closeEvent(QCloseEvent* ev) {
	if (denyClose) {
		ev->ignore();
	}
}


Screen::~Screen() {
	delete ui;
}