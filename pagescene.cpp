#include <QTextCodec>
#include <QDebug>
#include "screen.h"
#include "pagescene.h"
#include "getfile.h"
#include "recommand.h"

PageScene::PageScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::Page) {
	ui->setupUi(this);
	filepath = father->currentPage;
	ID = father->currentID;
	qDebug() << "id of displayed file is" << ID << "\n";
	recommandID = _recommand(ID, father->score, father->totalArticles, father->totalWords);
	qDebug() << "recommand id and filename:\n";
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

	string subdir;
	getSubDir(subdir, "\input");//input�����ļ�����"xxxx\\input"
	//��ʾ������
	loadingMovie = new QMovie(":/news_system_ui/images/loading.gif");
	loading = new QLabel(this);
	loading->setGeometry(300, 300, 100, 100);
	loading->setMovie(loadingMovie);
	loadingMovie->start();
	loading->show();
	qDebug() << "loading label\n";
	//��ʾ���ؽ���
	loadingBar = new QProgressBar(this);
	loadingBar->setValue(0);
	loadingBar->setGeometry(100, 450, 600, 10);
	loadingBar->show();
	qDebug() << "loading bar\n";

	ui->webEngineView->load(QUrl::fromLocalFile(filepath));
	connect(ui->webEngineView, SIGNAL(loadStarted()), this, SLOT(viewLoadStart()));
	connect(ui->webEngineView, SIGNAL(loadProgress(int)), this, SLOT(viewLoadProgress(int)));
	connect(ui->webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(viewLoadFinished(bool)));

	totalArticles = recommandID.size();//�Ƽ����µ�����
	recommandList = new QLabel*[totalArticles];//�Ƽ��б�
	int height = (800 - ui->label->height()) / totalArticles;//һ���Ƽ��ı���ĸ߶�

	for (int i = 0, len = recommandID.size(); i < len; i++) {
		char fileid[10];
		int id = recommandID[i];
		itoa(id, fileid, 10);
		string filename =subdir + "\\" + string(fileid) + ".html";//�ļ��� xxx\\input\\0.html
		QString title = QString::fromLocal8Bit(father->ID2title[id].c_str());//����
		QString href = "<a href=";
		href += QString(filename.c_str());
		href += "\">";
		QString text = href + title;
		qDebug() << "filepath+title in the label is" << text << "\n";
		recommandList[i] = new QLabel(text, this);
		int startx = ui->webEngineView->width() + 20;
		int width = 1100 - startx;
		recommandList[i]->setGeometry(startx,height*i,width,height);
		connect(recommandList[i], SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));
		recommandList[i]->show();
	}
	//TODO������
	this->show();
}

void PageScene::openUrl(QString str) {
	//ͨ��str��ȡ�������ҳ��id  str=xxx\\input\\0.html
	int startidx = str.lastIndexOf("\\");
	int endidx = str.lastIndexOf(".html");//[start+1,end-1]
	QString idstr = str.mid(startidx + 1, endidx - 1 - startidx);
	QByteArray ba = idstr.toLocal8Bit();
	char* data = ba.data();
	father->currentID = atoi(data);//�޸�father��ǰ������ת����ҳ��ID
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	emit toPage(path);//������ת������html���ź�
}

void PageScene::viewLoadProgress(int progress) {
	if (progress >= 0 && progress <= 100) {
		loadingBar->setValue(progress);
		qDebug() << progress << '\n';
	}
}

void PageScene::viewLoadFinished(bool ok) {
	if (ok) {
		loading->setVisible(false);
		loadingBar->setVisible(false);//Ϊ�˱��ⲻ��Ҫ��bug������ǰdelete��ǰ�����ϵ����
		qDebug() << "loading finished!\n";
	}
}

void PageScene::viewLoadStart() {
	qDebug() << "loading start!\n";
}

PageScene::~PageScene() {
	delete recommandList;
	delete loadingMovie;
	delete ui;
}
