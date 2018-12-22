#ifndef SCREEN_H
#define SCREEN_H

//#include "ui_news_system_ui.h"
#include "ui_DialogButtonRight.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"
#include <QDialog>
#include "scene.h"
#include "Stack.h"
#include "hashtable.h"
#include "dictionary.h"

class Extractor;//进行网页解析的线程


class Screen :public QDialog {
	Q_OBJECT 

public:
	/*
		在多次搜索中保持不变的变量
	*/
	BalanceBinaryTree* tree = new BalanceBinaryTree;//倒排索引
	int* id2wordnum = NULL;//每个ID的文章中包含的总词数
	int totalArticles = 0, totalWords = 0;//文章总数，词语总数
	map<CharString, int> title2ID;//从新闻标题到ID的映射
	map<int, CharString> ID2title;//从ID到标题的映射
	double** score;//打分矩阵
	double** sim;//相似度矩阵
	HashTable dic, stop;//词库
	/*
		每次重新搜索时都会清空的变量
	*/
	vector<pair<int, int>> ret;//通过关键词查询文件，返回<id,times>的pair
	vector<int> clickedLinks;//列表页上被点击过的链接的位置（从上往下数第几个）
	QString currentPage;//当前即将跳转的文件的名称
	Stack<QString> pages;//所有打开过的文件名，按时间顺序入栈
	int currentID;//当前即将跳转的文件的ID
	Stack<int> IDs;//所有打开过的文件的ID，按照时间顺序入栈
	vector<int> currentRecommand;//当前即将跳转文件的推荐文件
	Stack<vector<int>> recommands;//所有打开过的文件对应的推荐列表，按照时间顺序入栈
	vector<vector<int>> clickedPagelinks;//新闻页上已经点击过的链接

	explicit Screen(QWidget* parent = 0);
	~Screen();

private:
	Scene* scene;//场景类
	Ui::Dialog* ui;//指向ui的指针
	Extractor* extractor;//载入数据的线程
	void closeEvent(QCloseEvent* event);
	bool denyClose = true;//一开始载入数据时禁止关闭窗口

public slots:
	void handleProcessed(int value);//解析文件进度
	void startExtract();//开始解析文件
	void getArticleID(char* sent);//根据关键词查询文章ID
	void jumpToPage(QString str);//从列表跳转到page
	void jumpToLastPage();//回到上一个网页
	void jumpToInput();//回到输入框，清空所有搜索历史
};

#endif 