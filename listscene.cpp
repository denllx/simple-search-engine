#include <QUrl>
#include <QDesktopServices>
#include <QString>
#include <QDebug>
#include <QLatin1String>
#include "screen.h"
#include "listscene.h"
#include "getfile.h"//通过ID获取文件路径

ListScene::ListScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::List) {
	ui->setupUi(this);
	totalArticles = father->ret.size();//解析到的文章数量
	//初始化每个文章标题对应的label
	list = new QLabel*[totalArticles];
	int height = (int)(600 / totalArticles);//一个标题的高度
	string inputdir;
	getSubDir(inputdir, "\input");//获取input文件夹所在路径，即xxx/input
	for (int i = 0; i < totalArticles; i++) {
		//为每个label添加跳转的文件名链接
		//QString href = "<a href=\"http://www.cnblog.com/fron_csl\">";//无效链接，只是为了让文本看起来像超链接
		char fileid[10];
		itoa(i, fileid, 10);
		string filename = inputdir + "\\"+string(fileid) + ".html";//文件名 xxx\\input\\0.html
		QString title=QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());//标题
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
	//将末尾的"\去掉
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	qDebug() << "jump to file:" << path << "\n";//str=xxx\\input\\0.html
	emit toPage(path);//发送跳转到具体html的信号
}

ListScene::~ListScene() {

}
