#ifndef LISTSCENE_H
#define LISTSCENE_H
#include "scene.h"
#include "ui_list.h"

using namespace Ui;

//所有搜索结果的列表
class ListScene :public Scene {
	Q_OBJECT
private:
	QLabel** list;//每个QLabel显示一个标题，个数通过Screen确定
	Ui::List* ui;
	int totalArticles;//关键词对应的文章总数，通过father获取
public:
	explicit ListScene(QWidget* parent = 0);
	~ListScene();

public slots:
	void openUrl(QString);
};

#endif 