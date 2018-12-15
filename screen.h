#ifndef SCREEN_H
#define SCREEN_H

#include "ui_news_system_ui.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"

class Extractor;//������ҳ�������߳�

class Screen :public QMainWindow {
	Q_OBJECT 

public:
	BalanceBinaryTree* tree = new BalanceBinaryTree;//��������
	int* id2wordnum = NULL;//ÿ��ID�������а������ܴ���
	int totalArticles = 0, totalWords = 0;//������������������
	map<CharString, int> title2ID;//�����ű��⵽ID��ӳ��
	map<int, CharString> ID2title;//��ID�������ӳ��

	Screen(QWidget* parent = 0);
	~Screen();

private:
	Ui::news_system_uiClass ui;

public slots:
	//void changeText();
	void handleProcessed(int value);//�����ļ�����
	void startExtract();//��ʼ�����ļ�
};

#endif 