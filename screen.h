#ifndef SCREEN_H
#define SCREEN_H

#include "ui_news_system_ui.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"

class Extractor;//进行网页解析的线程

class Screen :public QMainWindow {
	Q_OBJECT 

public:
	BalanceBinaryTree* tree = new BalanceBinaryTree;//倒排索引
	int* id2wordnum = NULL;//每个ID的文章中包含的总词数
	int totalArticles = 0, totalWords = 0;//文章总数，词语总数
	map<CharString, int> title2ID;//从新闻标题到ID的映射
	map<int, CharString> ID2title;//从ID到标题的映射

	Screen(QWidget* parent = 0);
	~Screen();

private:
	Ui::news_system_uiClass ui;

public slots:
	//void changeText();
	void handleProcessed(int value);//解析文件进度
	void startExtract();//开始解析文件
};

#endif 