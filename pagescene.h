#ifndef PAGESCENE_H
#define PAGESCENE_H

#include "scene.h"
#include"ui_page.h"
#include <vector>
#include <QProgressBar>
#include <iostream>
#include <QMovie>

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
	QLabel** recommandAbst;//ÿ��QLabel��ʾһ��ժҪ���ڱ����·�
	//QLabel* loading;//��load��δ���ʱ��ʾתȦȦ
	//QProgressBar* loadingBar;//��loading��δ���ʱѡ�����
	//QMovie* loadingMovie;//loading��ͼƬ
	Ui::Page* ui;
	int totalArticles;//�Ƽ��б������������ͨ��father��ȡ
	int ID;//��ǰ���µ�ID
	QString filepath;//��ǰ���µ�path����file:///��ͷ	
	vector<int> recommandID;//�Ƽ����µ�ID
public:
	explicit PageScene(QWidget* parent = 0);
	~PageScene();

public slots:
	void openUrl(QString str);//�����ת

signals:
	void toPage(QString filename);//��ת����Ӧ�ļ���
	void backPage();//�ص���һҳ
};


#endif 