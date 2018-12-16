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
	int height = (int)(600 / totalArticles);//һ������ĸ߶�
	string inputdir;
	getSubDir(inputdir, "\input");//��ȡinput�ļ�������·������xxx/input
	for (int i = 0; i < totalArticles; i++) {
		//Ϊÿ��label�����ת���ļ�������
		//QString href = "<a href=\"http://www.cnblog.com/fron_csl\">";//��Ч���ӣ�ֻ��Ϊ�����ı�������������
		char fileid[10];
		itoa(i, fileid, 10);
		string filename = inputdir + "\\"+string(fileid) + ".html";//�ļ��� xxx\\input\\0.html
		QString title=QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());//����
		QString href = "<a href=";
		href += QString(filename.c_str());
		href += "\">";
		QString text = href + title;
		qDebug() << "filepath+title in the label is" << text << "\n";
		list[i] = new QLabel(text,this);
		list[i]->setGeometry(100, height*i, 600, height);
		connect(list[i], SIGNAL(linkActivated(QString)),
			this, SLOT(openUrl(QString)));
		list[i]->show();
	}
	this->show();
}

//str=filepath
void ListScene::openUrl(QString str) {
	//QDesktopServices::openUrl(QUrl(str));
	//��ĩβ��"\ȥ��
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	qDebug() << "jump to file:" << path << "\n";//str=xxx\\input\\0.html
	emit toPage(path);//������ת������html���ź�
}

ListScene::~ListScene() {

}
