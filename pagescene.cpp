#include "screen.h"
#include "pagescene.h"
#include "getfile.h"

PageScene::PageScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Page) {
	ui->setupUi(this);
	//TODO ͨ��father(screen)��ȡID
	ID = 0;//�Խ��ƪ
	//TODO ͨ��father��ȡrecommandList
	recommandID = vector<int>{ 1,2,3 };
	//ͨ��ID��ȡ�ļ���
	string subdir;
	getSubDir(subdir, "\input");//input�����ļ�����"xxxx/input"
	char strid[10];
	itoa(ID,strid,10);
	subdir += string(strid);
	subdir += ".html";
	QString url = QString(subdir.c_str());
	qDebug() << "filename:"<<url << "\n";
	//��ʾ��ǰ����
	ui->webEngineView->load(QUrl(url));
	totalArticles = recommandID.size();//�Ƽ����µ�����
	recommandList = new QLabel*[totalArticles];
	int height = (600 - ui->label->height()) / totalArticles;//һ���Ƽ��ı���ĸ߶�
	//ͨ��recommandList��ȡ�Ƽ����µı���
	for (int i = 0, len = recommandID.size(); i < len; i++) {
		QString href = "a <href="">";
		QString title = father->ID2title[recommandID[i]].c_str();
		QString text = href + title;
		recommandList[i] = new QLabel(text, this);
		recommandList[i]->show();
	}
	//TODO������
	this->show();
}


PageScene::~PageScene() {

}
