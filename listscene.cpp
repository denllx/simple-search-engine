#include <QUrl>
#include <QDesktopServices>
#include <QString>
#include <QDebug>
#include <QLatin1String>
#include "screen.h"
#include "listscene.h"
#include "getfile.h"//ͨ��ID��ȡ�ļ�·��

ListScene::ListScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::List) {
	ui->setupUi(this);
	totalArticles = father->ret.size();//����������������
	//��ʼ��ÿ�����±����Ӧ��label
	list = new QLabel*[totalArticles];
	int height = (int)(800 / totalArticles);//һ������ĸ߶�
	string inputdir;
	getSubDir(inputdir, "\input");//��ȡinput�ļ�������·������xxx/input
	for (int i = 0; i < totalArticles; i++) {
		char fileid[10];
		itoa(father->ret[i].first, fileid, 10);
		string filename = inputdir + "\\"+string(fileid) + ".html";//�ļ��� xxx\\input\\y.html
		QString title=QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());//����
		QString href = "<a href=";
		href += QString(filename.c_str());
		href += "\">";
		QString text = href + title;
		list[i] = new QLabel(text,this);
		list[i]->setGeometry(100, height*i, 1000, height);
		connect(list[i], SIGNAL(linkActivated(QString)),
			this, SLOT(openUrl(QString)));
		list[i]->show();
	}
	this->show();
}

//str=filepath
void ListScene::openUrl(QString str) {
	//��ĩβ��"\ȥ��
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	emit toPage(path);//������ת������html���ź�
}

ListScene::~ListScene() {
	delete ui;
}
