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

//有多少个文件已经被解析
void Screen::handleProcessed(int value) {
	if (value == -1) {//解析完成
		//删除线程
		extractor->quit();
		//确定总词数
		totalWords = tree->size();
		//显示输入场景
		scene = new InputScene(this);
		//用户点击确认后，接收来自场景的字符串并分词
		connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
		denyClose = false;//之后允许用户关闭窗口
	}
	ui->progressBar->setValue(value);
}

//接收输入界面传来的字符串
//找到包含关键词最多的文章ID列表
void Screen::getArticleID(char* sent) {
	CharStringLink words;
	getInput(sent, words,dic,stop);	
	ret = query(tree, words);
	qDebug() << "recommanded list IDs";
	for (int i=0;i<ret.size();i++)
		qDebug() << ret[i];
	//将ret中的所有ID传给列表界面
	scene->deleteLater();
	scene = new ListScene(this);
	connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
	connect(scene, SIGNAL(toInput()), this, SLOT(jumpToInput()));
}


//从xxx.info的文件名中提取ID
int filename2id(const QString& str) {
	//获从文件名获取文件的ID
	int end = str.lastIndexOf(".info");
	int start = str.lastIndexOf("\\");
	//数字在[start+1,end-1]
	QString numStr = str.mid(start + 1, end - 1 - start);
	QByteArray ba = numStr.toLatin1();
	char* cnum = ba.data();
	return atoi(cnum);
}

//处理点击链接后传来的页面跳转信号
void Screen::jumpToPage(QString str) {
	qDebug() << "screen::jump to page";
	currentPage = str;//xxx\\output\\0.info
	pages.push(currentPage);
	currentID=filename2id(currentPage);
	IDs.push(currentID);
	//如果不是第一个页面，将页面加入上一个页面的点击列表
	if (!clickedPagelinks.empty()) {
		qDebug() << "clickedpagelinks.size:" << clickedPagelinks.size();
		clickedPagelinks[clickedPagelinks.size() - 1].push_back(currentID);
	}
	clickedPagelinks.push_back(vector<int>(0));//打开一个新的页面，对应一个空的点击列表
	//计算推荐列表
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

//处理点击后退按钮后传来的跳转信号
void Screen::jumpToLastPage() {
	qDebug() << "jump to to last page";
	
	if (IDs.size()>1) {//当前不是第一个网页
		//取得上一页的ID,文件名，推荐ID列表
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
	else {//第一个新闻页面后退，返回列表页
		//获取最后一个被点击的新闻ID
		int lastID = IDs.top();
		IDs.pop();
		pages.pop();
		recommands.pop();
		currentPage = "";
		currentRecommand = vector<int>(0);
		currentID = -1;
		clickedPagelinks.pop_back();
		//找到上一个被点击过的网页
		int i =0,len=ret.size();
		for (; i < len; i++) {
			if (ret[i].first == lastID) break;
		}
		if (i != len) {//找到了上一个被点击过的网页
			clickedLinks.push_back(i);
			sort(clickedLinks.begin(), clickedLinks.end());
		}
		//返回列表页
		scene->deleteLater();
		qDebug() << "clicked linkgs:";
		for (int i = 0; i < clickedLinks.size(); i++) qDebug() << clickedLinks[i] << " ";
		scene = new ListScene(this);
		connect(scene, SIGNAL(toPage(QString)), this, SLOT(jumpToPage(QString)));
		connect(scene, SIGNAL(toInput()), this, SLOT(jumpToInput()));
	}
}

//处理从列表界面传来的回到搜索界面的信号
void Screen::jumpToInput() {
	qDebug() << "jump to input";
	//清空搜索历史
	ret.clear();
	clickedLinks.clear();
	clickedPagelinks.clear();
	currentPage = "";
	currentID = -1;
	IDs.clear();
	currentRecommand.clear();
	recommands.clear();
	//构造搜索界面
	qDebug() << "build input scene";
	scene->deleteLater();
	scene = new InputScene(this);
	connect(scene, SIGNAL(confirmed(char*)), this, SLOT(getArticleID(char*)));
}

void Screen::startExtract()//开始解析文件的进程
{
	extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
	//设置窗口为不可关闭，防止发生线程运行时中断错误
	//setwindowFlags(QT::window | Qt::Framelesswindowhint | QT::windowTitlehint)
	//setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowTitleHint);	
}

//禁止关闭窗口
void Screen::closeEvent(QCloseEvent* ev) {
	if (denyClose) {
		ev->ignore();
	}
}


Screen::~Screen() {
	delete ui;
}