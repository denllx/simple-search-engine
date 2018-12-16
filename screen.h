#ifndef SCREEN_H
#define SCREEN_H

//#include "ui_news_system_ui.h"
#include "ui_DialogButtonRight.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"
#include <QDialog>
#include "scene.h"

class Extractor;//������ҳ�������߳�


class Screen :public QDialog {
	Q_OBJECT 

public:
	BalanceBinaryTree* tree = new BalanceBinaryTree;//��������
	int* id2wordnum = NULL;//ÿ��ID�������а������ܴ���
	int totalArticles = 0, totalWords = 0;//������������������
	map<CharString, int> title2ID;//�����ű��⵽ID��ӳ��
	map<int, CharString> ID2title;//��ID�������ӳ��
	vector<pair<int, int>> ret;//ͨ���ؼ��ʲ�ѯ�ļ�������<id,times>��pair
	QString currentPage;//��ǰ������ת���ļ�������
	int currentID;//��ǰ������ת���ļ���ID
	double** score;//��־���
	explicit Screen(QWidget* parent = 0);
	~Screen();

private:
	Scene* scene;//������
	Ui::Dialog* ui;//ָ��ui��ָ��

public slots:
	void handleProcessed(int value);//�����ļ�����
	void startExtract();//��ʼ�����ļ�
	void getArticleID(char* sent);//���ݹؼ��ʲ�ѯ����ID
	void jumpToPage(QString str);//���б���ת��page
	void jumpToAnotherPage(QString str);//��һ��page��ת����һ��page
};

#endif 