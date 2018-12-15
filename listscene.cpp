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
	totalArticles = father->ret.size();//����������������
	//��ʼ��ÿ�����±����Ӧ��label
	list = new QLabel*[totalArticles];
	int height = (int)(600 / totalArticles);//һ������ĸ߶�
	for (int i = 0; i < totalArticles; i++) {
		//Ϊÿ��label�����ת���ļ�������
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

//��ת��str���ڵ���ҳ
void ListScene::openUrl(QString str) {
	QDesktopServices::openUrl(QUrl(str));
}

ListScene::~ListScene() {

}
