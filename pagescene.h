#ifndef PAGESCENE_H
#define PAGESCENE_H

#include "scene.h"
#include"ui_page.h"
#include <vector>

/*
	����htmlҳ��
	���Ҳ���ʾ�Ƽ����ŵı���
*/


using namespace Ui;

//��������������б�
class PageScene :public Scene {
	Q_OBJECT
private:
	QLabel** recommandList;//ÿ��QLabel��ʾһ�����⣬����ͨ��Screenȷ��
	Ui::Page* ui;
	int totalArticles;//�Ƽ��б������������ͨ��father��ȡ
	int ID;//��ǰ���µ�ID
	vector<int> recommandID;//�Ƽ����µ�ID
public:
	explicit PageScene(QWidget* parent = 0);
	~PageScene();

public slots:
};


#endif 