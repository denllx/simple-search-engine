#include "screen.h"
#include "pagescene.h"
#include "getfile.h"

PageScene::PageScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Page) {
	ui->setupUi(this);
	//TODO 通过father(screen)获取ID
	ID = 0;//杨超越那篇
	//TODO 通过father获取recommandList
	recommandID = vector<int>{ 1,2,3 };
	//通过ID获取文件名
	string subdir;
	getSubDir(subdir, "\input");//input所在文件名，"xxxx/input"
	char strid[10];
	itoa(ID,strid,10);
	subdir += string(strid);
	subdir += ".html";
	QString url = QString(subdir.c_str());
	qDebug() << "filename:"<<url << "\n";
	//显示当前文章
	ui->webEngineView->load(QUrl(url));
	totalArticles = recommandID.size();//推荐文章的总数
	recommandList = new QLabel*[totalArticles];
	int height = (600 - ui->label->height()) / totalArticles;//一个推荐的标题的高度
	//通过recommandList获取推荐文章的标题
	for (int i = 0, len = recommandID.size(); i < len; i++) {
		QString href = "a <href="">";
		QString title = father->ID2title[recommandID[i]].c_str();
		QString text = href + title;
		recommandList[i] = new QLabel(text, this);
		recommandList[i]->show();
	}
	//TODO绑定链接
	this->show();
}


PageScene::~PageScene() {

}
