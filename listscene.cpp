#include <QUrl>
#include <QDesktopServices>
#include <QString>
#include <QDebug>
#include <QLatin1String>
#include "screen.h"
#include "listscene.h"

ListScene::ListScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::List) {
	ui->setupUi(this);
	totalArticles = father->ret.size();//解析到的文章数量
	//初始化每个文章标题对应的label
	list = new QLabel*[totalArticles];
	int height = (int)(600 / totalArticles);//一个标题的高度
	for (int i = 0; i < totalArticles; i++) {
		//为每个label添加跳转的文件名链接
		QString href = "<a href=\"http://www.cnblog.com/fron_csl\">";
		QString display=QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());
		QString text = href + display;
		list[i] = new QLabel(text,this);
		list[i]->setGeometry(100, height*i, 600, height);
		connect(list[i], SIGNAL(linkActivated(QString)),
			this, SLOT(openUrl(QString)));
		list[i]->show();
	}
	this->show();
}

//跳转到str所在的网页
void ListScene::openUrl(QString str) {
	QDesktopServices::openUrl(QUrl(str));
}

ListScene::~ListScene() {

}
