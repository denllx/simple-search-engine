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
	filepath = father->currentPage;//��ǰ��ҳ������(xxx.info)
	ID = father->currentID;//��ǰ��ҳ��ID
	recommandID = father->currentRecommand;//��ǰ��ҳ���Ƽ���ID�б�

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));//֧������

	string subdir;
	getSubDir(subdir, "\output");//output�ļ���·����"xxxx\\output"
	//��ʾ������
	/*loadingMovie = new QMovie(":/news_system_ui/images/loading.gif");
	loading = new QLabel(this);
	loading->setGeometry(300, 300, 100, 100);
	loading->setMovie(loadingMovie);
	loadingMovie->start();
	loading->show();*/
	//��ʾ���ؽ���
	/*loadingBar = new QProgressBar(this);
	loadingBar->setValue(0);
	loadingBar->setGeometry(100, 450, 600, 10);
	loadingBar->show();*/

	//��.info�ж�ȡ������Ϣ
	QByteArray ba = father->currentPage.toLatin1();
	ifstream fin(ba.data());
	string title;//����
	getline(fin, title);
	string time;//ʱ��
	getline(fin, time);
	string source;//��Դ
	getline(fin, source);
	string main,sentence;//����
	while (!fin.eof()) {
		fin >> sentence;
		main += sentence;
		main += '\n';
	}
	fin.close();
	//��browser����ʾ����
	ui->titlebrowser->setText(QString::fromLocal8Bit(title.c_str()));
	ui->titlebrowser->setAlignment(Qt::AlignCenter);
	ui->timebrowser->setText(QString::fromLocal8Bit(time.c_str()));
	ui->sourcebrowser->setText(QString::fromLocal8Bit(source.c_str()));
	ui->mainbrowser->setText(QString::fromLocal8Bit(main.c_str()));
	

	totalArticles = recommandID.size();//�Ƽ����µ�����
	recommandList = new QLabel*[totalArticles];//�Ƽ�����
	recommandAbst = new QLabel*[totalArticles];//�Ƽ�ժҪ
	int height = (800 - ui->label->height()) / totalArticles;//����+ժҪ�ĸ߶�
	int h1 = height * 0.3, h2 = height * 0.7;//���⣬ժҪ�ĸ߶�

	for (int i = 0, len = recommandID.size(); i < len; i++) {
		char fileid[10];
		int id = recommandID[i];
		itoa(id, fileid, 10);
		string filename =subdir + "\\" + string(fileid) + ".info";//�ļ��� xxx\\output\\0.info
		QString title = QString::fromLocal8Bit(father->ID2title[id].c_str());//����
		QString href = "<a href=";
		href += QString(filename.c_str());
		href += "\">";
		QString text = href + title;

		//���Ʊ���
		recommandList[i] = new QLabel(text, this);
		int startx = 800;
		int width = 1100 - startx;
		recommandList[i]->setGeometry(startx,height*i,width,h1);
		connect(recommandList[i], SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));//���������ת
		recommandList[i]->show();

		//����ժҪ
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
		recommandAbst[i]->setAlignment(Qt::AlignTop);//�Զ�����
		recommandAbst[i]->show();
	}

	//���˰�ť
	connect(ui->back, SIGNAL(clicked()), this, SIGNAL(backPage()));
	this->show();
}


/*
	������Ӻ��������ڷ����ź�
	strΪ��ת�ļ���+б�ܣ���xx.info\������б����Ϊ���������Ӹ�ʽ��
*/
void PageScene::openUrl(QString str) {
	//ȥ��ĩβ��б�ܣ�
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
