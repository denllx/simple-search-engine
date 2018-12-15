#ifndef LISTSCENE_H
#define LISTSCENE_H
#include "scene.h"
#include "ui_list.h"

using namespace Ui;

//��������������б�
class ListScene :public Scene {
	Q_OBJECT
private:
	QLabel** list;//ÿ��QLabel��ʾһ�����⣬����ͨ��Screenȷ��
	Ui::List* ui;
	int totalArticles;//�ؼ��ʶ�Ӧ������������ͨ��father��ȡ
public:
	explicit ListScene(QWidget* parent = 0);
	~ListScene();

public slots:
	void openUrl(QString);
};

#endif 