#ifndef SCREEN_H
#define SCREEN_H

//#include "ui_news_system_ui.h"
#include "ui_DialogButtonRight.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"
#include <QDialog>
#include "scene.h"

class Extractor;//进行网页解析的线程


class Screen :public QDialog {
	Q_OBJECT 

public:
	BalanceBinaryTree* tree = new BalanceBinaryTree;//倒排索引
	int* id2wordnum = NULL;//每个ID的文章中包含的总词数
	int totalArticles = 0, totalWords = 0;//文章总数，词语总数
	map<CharString, int> title2ID;//从新闻标题到ID的映射
	map<int, CharString> ID2title;//从ID到标题的映射
	vector<pair<int, int>> ret;//通过关键词查询文件，返回<id,times>的pair
	QString currentPage;//当前即将跳转的文件的名称
	int currentID;//当前即将跳转的文件的ID
	double** score;//打分矩阵
	explicit Screen(QWidget* parent = 0);
	~Screen();

private:
	Scene* scene;//场景类
	Ui::Dialog* ui;//指向ui的指针

public slots:
	void handleProcessed(int value);//解析文件进度
	void startExtract();//开始解析文件
	void getArticleID(char* sent);//根据关键词查询文章ID
	void jumpToPage(QString str);//从列表跳转到page
	void jumpToAnotherPage(QString str);//从一个page跳转到另一个page
};

#endif 