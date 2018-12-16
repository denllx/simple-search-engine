#ifndef PAGESCENE_H
#define PAGESCENE_H

#include "scene.h"
#include"ui_page.h"
#include <vector>
#include <QProgressBar>
#include <iostream>
#include <QMovie>

/*
	返回html页面
	在右侧显示推荐新闻的标题
*/


using namespace std;

//所有搜索结果的列表
class PageScene :public Scene {
	Q_OBJECT
private:
	QLabel** recommandList;//每个QLabel显示一个标题，个数通过Screen确定
	QLabel* loading;//在load尚未完成时显示转圈圈
	QProgressBar* loadingBar;//在loading尚未完成时选择进度
	QMovie* loadingMovie;//loading的图片
	Ui::Page* ui;
	int totalArticles;//推荐列表的文章总数，通过father获取
	int ID;//当前文章的ID
	QString filepath;//当前文章的path，以file:///开头	
	vector<int> recommandID;//推荐文章的ID
public:
	explicit PageScene(QWidget* parent = 0);
	~PageScene();

public slots:
	void openUrl(QString str);
	void viewLoadProgress(int progress);//更改loadingBar的数值
	void viewLoadFinished(bool ok);//加载完成
	void viewLoadStart();//加载开始

signals:
	void toPage(QString url);
};


#endif 