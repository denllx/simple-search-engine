#include <QTextCodec>
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
	//qDebug() << "filepath:" << filepath << "\n";
	qDebug() << "id of displayed file is" << ID << "\n";
	//QByteArray ba = filepath.toLocal8Bit();
	//char* cfilename = ba.data();
	//qDebug() << "selected filename(without file:///):"<<QString(cfilename) << "\n";
	//ID = father->title2ID[cfilename];//��ѡ�е����µ�ID
	//qDebug() << "selected file ID=" << ID << "\n";
	//TODO ͨ��father��ȡrecommandList
	//recommandID = vector<int>{ 1,2,3 };
	recommandID = _recommand(ID, father->score, father->totalArticles, father->totalWords);
	qDebug() << "recommand id and filename:\n";
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	/*for (int i = 0, len = recommandID.size(); i < len; i++) {
		qDebug() << recommandID[i] << " " << QString::fromLocal8Bit(father->ID2title[recommandID[i]].c_str())<< "\n";
	}*/

	string subdir;
	getSubDir(subdir, "\input");//input�����ļ�����"xxxx\\input"
	//char strid[10];
	//itoa(ID,strid,10);
	//subdir += string(strid);
	//subdir += ".html";
	//qDebug() << "url:"<<filepath << "\n";
	//��ʾ��ǰ����
	ui->webEngineView->load(QUrl::fromLocalFile(filepath));
	totalArticles = recommandID.size();//�Ƽ����µ�����
	recommandList = new QLabel*[totalArticles];//�Ƽ��б�
	int height = (600 - ui->label->height()) / totalArticles;//һ���Ƽ��ı���ĸ߶�

	for (int i = 0, len = recommandID.size(); i < len; i++) {
		/*QString href = "a <href="">";
		QString title = father->ID2title[recommandID[i]].c_str();
		QString text = href + title;*/
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
		int width = 800 - startx;
		recommandList[i]->setGeometry(startx,height*i,width,height);
		connect(recommandList[i], SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));
		recommandList[i]->show();
	}
	//TODO������
	this->show();
}

void PageScene::openUrl(QString str) {
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	qDebug() << "jump to file:" << path << "\n";//str=xxx\\input\\0.html
	emit toPage(path);//������ת������html���ź�
}

PageScene::~PageScene() {

}
