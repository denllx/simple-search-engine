#include <QUrl>
#include <QDesktopServices>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QLatin1String>
#include "screen.h"
#include "listscene.h"
#include "getfile.h"//ͨ��ID��ȡ�ļ�·��

ListScene::ListScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::List) {
	totalArticles = father->ret.size();//����������������
	clickedLinks = father->clickedLinks;//����������µ�λ��
	
	ui->setupUi(this);
	//�õ��ʲ��ڷִʽ���У���ʾ��������
	if (totalArticles == 0) {
		qDebug() << "the word is not in the current vocabulary!";
		QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
		//û���ҵ�
		notfound = new QLabel(this);
		notfound->setText(QString::fromLocal8Bit("�ܱ�Ǹ��û���ҵ�����������ص���ҳ��"));
		notfound->setGeometry(200, 200, 700, 50);
		notfound->show();
		//��������
		tips = new QLabel(this);
		QString s1 = QString::fromLocal8Bit("��ܰ��ʾ��\n");
		QString s2 = QString::fromLocal8Bit("\t���������������Ƿ���ȷ\n");
		QString s3 = QString::fromLocal8Bit("\t������ҳδ��¼������վδ��¼�����ύ��ַ������\n");
		QString s4 = QString::fromLocal8Bit("\t�������κ�����ͽ��飬�뼰ʱ����������\n");
		QString strTip = s1 + s2 + s3 + s4;//��ʾ���
		tips->setText(strTip);
		tips->setWordWrap(true);//�Զ�����
		tips->setGeometry(200, 450, 700, 200);
		tips->show();
	}
	else {
		//��ʼ��ÿ�����±����Ӧ��UI�齨��������ռ�
		list = new QLabel*[totalArticles];
		abst = new QLabel*[totalArticles];
		int height = (int)(800 / totalArticles);//һ�������ժҪ���ܸ߶�
		int h1 = height * 0.3, h2 = height * 0.7;//����ռ0.3��ժҪռ0.7

		string inputdir;
		getSubDir(inputdir, "\output");//��ȡinput�ļ�������·������xxx/input

		int idx = 0;//��ǰ�ǵڼ����������������
		int numClicked = clickedLinks.size();//�ܹ��ж��ٸ��������������
		for (int i = 0; i < totalArticles; i++) {
			char fileid[10];
			itoa(father->ret[i].first, fileid, 10);//�����µ�ID

			//�Գ����ӵ���ʽ��ʾ����
			string filename = inputdir + "\\" + string(fileid) + ".info";
			QString title = QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());//����
			QString href = "<a ";
			if (idx < numClicked&& i == clickedLinks[idx]) {//����һ���Ѿ��������������
				idx++;
				href += "style='color:red;' ";//���ֱ��
			}
			href += "href=";
			href += QString(filename.c_str());
			href += "\">";
			QString text = href + title;
			list[i] = new QLabel(text, this);
			list[i]->setGeometry(200, height*i + 40, 700, h1);
			list[i]->setWordWrap(true);//�Զ�����
			connect(list[i], SIGNAL(linkActivated(QString)),
				this, SLOT(openUrl(QString)));

			//�ڱ����·���ʾժҪ
			ifstream fin(filename);
			string intitle, intime, insrc, inmain, sent1, sent2;
			getline(fin, intitle);
			getline(fin, intime);
			getline(fin, insrc);
			getline(fin, sent1);
			getline(fin, sent2);//����������Ϊ����
			fin.close();
			inmain = sent1 + sent2 + "...";
			abst[i] = new QLabel(QString::fromLocal8Bit(inmain.c_str()), this);
			abst[i]->setGeometry(200, height*i + h1 + 40, 700, h2);
			abst[i]->setWordWrap(true);
			abst[i]->setAlignment(Qt::AlignTop);//�Զ�����
		}

		for (int i = 0; i < totalArticles; i++) {
			list[i]->show();
			abst[i]->show();
		}
	}

	//������ˣ��ص��������
	connect(ui->back, SIGNAL(clicked()), this, SIGNAL(toInput()));
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
