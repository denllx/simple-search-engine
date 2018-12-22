#ifndef SCREEN_H
#define SCREEN_H

//#include "ui_news_system_ui.h"
#include "ui_DialogButtonRight.h"
#include "BalanceBinaryTree.h"
#include "CharStringLink.h"
#include <QDialog>
#include "scene.h"
#include "Stack.h"
#include "hashtable.h"
#include "dictionary.h"

class Extractor;//������ҳ�������߳�


class Screen :public QDialog {
	Q_OBJECT 

public:
	/*
		�ڶ�������б��ֲ���ı���
	*/
	BalanceBinaryTree* tree = new BalanceBinaryTree;//��������
	int* id2wordnum = NULL;//ÿ��ID�������а������ܴ���
	int totalArticles = 0, totalWords = 0;//������������������
	map<CharString, int> title2ID;//�����ű��⵽ID��ӳ��
	map<int, CharString> ID2title;//��ID�������ӳ��
	double** score;//��־���
	double** sim;//���ƶȾ���
	HashTable dic, stop;//�ʿ�
	/*
		ÿ����������ʱ������յı���
	*/
	vector<pair<int, int>> ret;//ͨ���ؼ��ʲ�ѯ�ļ�������<id,times>��pair
	vector<int> clickedLinks;//�б�ҳ�ϱ�����������ӵ�λ�ã������������ڼ�����
	QString currentPage;//��ǰ������ת���ļ�������
	Stack<QString> pages;//���д򿪹����ļ�������ʱ��˳����ջ
	int currentID;//��ǰ������ת���ļ���ID
	Stack<int> IDs;//���д򿪹����ļ���ID������ʱ��˳����ջ
	vector<int> currentRecommand;//��ǰ������ת�ļ����Ƽ��ļ�
	Stack<vector<int>> recommands;//���д򿪹����ļ���Ӧ���Ƽ��б�����ʱ��˳����ջ
	vector<vector<int>> clickedPagelinks;//����ҳ���Ѿ������������

	explicit Screen(QWidget* parent = 0);
	~Screen();

private:
	Scene* scene;//������
	Ui::Dialog* ui;//ָ��ui��ָ��
	Extractor* extractor;//�������ݵ��߳�
	void closeEvent(QCloseEvent* event);
	bool denyClose = true;//һ��ʼ��������ʱ��ֹ�رմ���

public slots:
	void handleProcessed(int value);//�����ļ�����
	void startExtract();//��ʼ�����ļ�
	void getArticleID(char* sent);//���ݹؼ��ʲ�ѯ����ID
	void jumpToPage(QString str);//���б���ת��page
	void jumpToLastPage();//�ص���һ����ҳ
	void jumpToInput();//�ص�������������������ʷ
};

#endif 