#ifndef LISTSCENE_H
#define LISTSCENE_H

#include <vector>
#include "scene.h"
#include "ui_list.h"

using namespace Ui;
using namespace std;

//所有搜索结果的列表
class ListScene :public Scene {
	Q_OBJECT
private:
	QLabel** list;//每个QLabel显示一个标题，个数通过Screen确定
	QLabel** abst;//每个标题下面有一段摘要
	QLabel* notfound;//告知没有找到相关网页
	QLabel* tips;//提醒用户重新输入
	Ui::List* ui;
	int totalArticles;//关键词对应的文章总数，通过father获取
	vector<int> clickedLinks;//点击过的文章是从上往下数第几个，通过father获取
public:
	explicit ListScene(QWidget* parent = 0);
	~ListScene();

public slots:
	void openUrl(QString);

signals:
	void toPage(QString str);//显示的文件名
	void toInput();			//跳转到输入界面，并清空输入框
};

#endif 