#ifndef PAGESCENE_H
#define PAGESCENE_H

#include "scene.h"
#include"ui_page.h"
#include <vector>
#include <iostream>

/*
	����htmlҳ��
	���Ҳ���ʾ�Ƽ����ŵı���
*/


using namespace std;

//��������������б�
class PageScene :public Scene {
	Q_OBJECT
private:
	QLabel** recommandList;//ÿ��QLabel��ʾһ�����⣬����ͨ��Screenȷ��
	Ui::Page* ui;
	int totalArticles;//�Ƽ��б������������ͨ��father��ȡ
	int ID;//��ǰ���µ�ID
	QString filepath;//��ǰ���µ�path����file:///��ͷ	
	vector<int> recommandID;//�Ƽ����µ�ID
public:
	explicit PageScene(QWidget* parent = 0);
	~PageScene();

public slots:
	void openUrl(QString str);

signals:
	void toPage(QString url);
};


#endif 