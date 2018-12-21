#include <QTextCodec>
#include <QDebug>
#include <string>
#include "screen.h"
#include "pagescene.h"
#include "getfile.h"
#include "recommand.h"

PageScene::PageScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Page) {
	ui->setupUi(this);
	filepath = father->currentPage;//当前网页的名称(xxx.info)
	ID = father->currentID;//当前网页的ID
	recommandID = father->currentRecommand;//当前网页的推荐的ID列表

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));//支持中文

	string subdir;
	getSubDir(subdir, "\output");//output文件夹路径，"xxxx\\output"
	//显示加载中
	/*loadingMovie = new QMovie(":/news_system_ui/images/loading.gif");
	loading = new QLabel(this);
	loading->setGeometry(300, 300, 100, 100);
	loading->setMovie(loadingMovie);
	loadingMovie->start();
	loading->show();*/
	//显示加载进度
	/*loadingBar = new QProgressBar(this);
	loadingBar->setValue(0);
	loadingBar->setGeometry(100, 450, 600, 10);
	loadingBar->show();*/

	//从.info中读取文章信息
	QByteArray ba = father->currentPage.toLatin1();
	ifstream fin(ba.data());
	string title;//标题
	getline(fin, title);
	string time;//时间
	getline(fin, time);
	string source;//来源
	getline(fin, source);
	string main,sentence;//正文
	while (!fin.eof()) {
		fin >> sentence;
		main += sentence;
		main += '\n';
	}
	fin.close();
	//在browser中显示文章
	ui->titlebrowser->setText(QString::fromLocal8Bit(title.c_str()));
	ui->titlebrowser->setAlignment(Qt::AlignCenter);
	ui->timebrowser->setText(QString::fromLocal8Bit(time.c_str()));
	ui->sourcebrowser->setText(QString::fromLocal8Bit(source.c_str()));
	ui->mainbrowser->setText(QString::fromLocal8Bit(main.c_str()));
	

	totalArticles = recommandID.size();//推荐文章的总数
	recommandList = new QLabel*[totalArticles];//推荐标题
	recommandAbst = new QLabel*[totalArticles];//推荐摘要
	int height = (800 - ui->label->height()) / totalArticles;//标题+摘要的高度
	int h1 = height * 0.3, h2 = height * 0.7;//标题，摘要的高度

	for (int i = 0, len = recommandID.size(); i < len; i++) {
		char fileid[10];
		int id = recommandID[i];
		itoa(id, fileid, 10);
		string filename =subdir + "\\" + string(fileid) + ".info";//文件名 xxx\\output\\0.info
		QString title = QString::fromLocal8Bit(father->ID2title[id].c_str());//标题
		QString href = "<a href=";
		href += QString(filename.c_str());
		href += "\">";
		QString text = href + title;

		//绘制标题
		recommandList[i] = new QLabel(text, this);
		int startx = 800;
		int width = 1100 - startx;
		recommandList[i]->setGeometry(startx,height*i,width,h1);
		connect(recommandList[i], SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));//点击链接跳转
		recommandList[i]->show();

		//绘制摘要
		ifstream fin(filename);
		string intitle, intime, insrc, inmain, sent1, sent2;
		getline(fin, intitle);
		getline(fin, intime);
		getline(fin, insrc);
		getline(fin, inmain);
		getline(fin, sent1);
		getline(fin, sent2);
		inmain = sent1 + sent2 + "...";
		fin.close();
		recommandAbst[i] = new QLabel(QString::fromLocal8Bit(inmain.c_str()), this);
		recommandAbst[i]->setGeometry(startx, height*i + h1, width, h2);
		//recommandAbst[i]->adjustSize();
		recommandAbst[i]->setWordWrap(true);
		recommandAbst[i]->setAlignment(Qt::AlignTop);//自动换行
		recommandAbst[i]->show();
	}

	//后退按钮
	connect(ui->back, SIGNAL(clicked()), this, SIGNAL(backPage()));
	this->show();
}


/*
	点击链接后向主窗口发送信号
	str为跳转文件名+斜杠，即xx.info\（加上斜杠是为了满足链接格式）
*/
void PageScene::openUrl(QString str) {
	//去掉末尾的斜杠！
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	qDebug() << "open url:" <<path << endl;
	emit toPage(path);
}

PageScene::~PageScene() {
	delete recommandList;
	//delete loadingMovie;
	delete ui;
}
