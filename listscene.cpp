#include <QUrl>
#include <QDesktopServices>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QLatin1String>
#include "screen.h"
#include "listscene.h"
#include "getfile.h"//通过ID获取文件路径

ListScene::ListScene(QWidget* parent) :
	Scene(parent),
	ui(new Ui::List) {
	totalArticles = father->ret.size();//解析到的文章数量
	clickedLinks = father->clickedLinks;//点击过的文章的位置
	
	ui->setupUi(this);
	//该单词不在分词结果中，提示重新搜索
	if (totalArticles == 0) {
		qDebug() << "the word is not in the current vocabulary!";
		QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
		//没有找到
		notfound = new QLabel(this);
		notfound->setText(QString::fromLocal8Bit("很抱歉，没有找到您的输入相关的网页！"));
		notfound->setGeometry(200, 200, 700, 50);
		notfound->show();
		//重新输入
		tips = new QLabel(this);
		QString s1 = QString::fromLocal8Bit("温馨提示：\n");
		QString s2 = QString::fromLocal8Bit("\t·请检查您的输入是否正确\n");
		QString s3 = QString::fromLocal8Bit("\t·如网页未收录或者新站未收录，请提交网址给我们\n");
		QString s4 = QString::fromLocal8Bit("\t·如有任何意见和建议，请及时反馈给我们\n");
		QString strTip = s1 + s2 + s3 + s4;//提示语句
		tips->setText(strTip);
		tips->setWordWrap(true);//自动换行
		tips->setGeometry(200, 450, 700, 200);
		tips->show();
	}
	else {
		//初始化每个文章标题对应的UI组建，并分配空间
		list = new QLabel*[totalArticles];
		abst = new QLabel*[totalArticles];
		int height = (int)(800 / totalArticles);//一个标题和摘要的总高度
		int h1 = height * 0.3, h2 = height * 0.7;//标题占0.3，摘要占0.7

		string inputdir;
		getSubDir(inputdir, "\output");//获取input文件夹所在路径，即xxx/input

		int idx = 0;//当前是第几个被点击过的链接
		int numClicked = clickedLinks.size();//总共有多少个被点击过的链接
		for (int i = 0; i < totalArticles; i++) {
			char fileid[10];
			itoa(father->ret[i].first, fileid, 10);//该文章的ID

			//以超链接的形式显示标题
			string filename = inputdir + "\\" + string(fileid) + ".info";
			QString title = QString::fromLocal8Bit(father->ID2title[father->ret[i].first].c_str());//标题
			QString href = "<a ";
			if (idx < numClicked&& i == clickedLinks[idx]) {//这是一个已经被点击过的链接
				idx++;
				href += "style='color:red;' ";//文字变红
			}
			href += "href=";
			href += QString(filename.c_str());
			href += "\">";
			QString text = href + title;
			list[i] = new QLabel(text, this);
			list[i]->setGeometry(200, height*i + 40, 700, h1);
			list[i]->setWordWrap(true);//自动换行
			connect(list[i], SIGNAL(linkActivated(QString)),
				this, SLOT(openUrl(QString)));

			//在标题下方显示摘要
			ifstream fin(filename);
			string intitle, intime, insrc, inmain, sent1, sent2;
			getline(fin, intitle);
			getline(fin, intime);
			getline(fin, insrc);
			getline(fin, sent1);
			getline(fin, sent2);//读入两行作为正文
			fin.close();
			inmain = sent1 + sent2 + "...";
			abst[i] = new QLabel(QString::fromLocal8Bit(inmain.c_str()), this);
			abst[i]->setGeometry(200, height*i + h1 + 40, 700, h2);
			abst[i]->setWordWrap(true);
			abst[i]->setAlignment(Qt::AlignTop);//自动换行
		}

		for (int i = 0; i < totalArticles; i++) {
			list[i]->show();
			abst[i]->show();
		}
	}

	//点击后退，回到输入界面
	connect(ui->back, SIGNAL(clicked()), this, SIGNAL(toInput()));
	this->show();
}

//str=filepath
void ListScene::openUrl(QString str) {
	//将末尾的"\去掉
	int length = str.size() - 1;
	QString path = str.mid(0, length);
	emit toPage(path);//发送跳转到具体html的信号
}

ListScene::~ListScene() {
	delete ui;
}
