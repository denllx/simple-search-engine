#ifndef LISTSCENE_H
#define LISTSCENE_H

#include <vector>
#include "scene.h"
#include "ui_list.h"

using namespace Ui;
using namespace std;

//��������������б�
class ListScene :public Scene {
	Q_OBJECT
private:
	QLabel** list;//ÿ��QLabel��ʾһ�����⣬����ͨ��Screenȷ��
	QLabel** abst;//ÿ������������һ��ժҪ
	QLabel* notfound;//��֪û���ҵ������ҳ
	QLabel* tips;//�����û���������
	Ui::List* ui;
	int totalArticles;//�ؼ��ʶ�Ӧ������������ͨ��father��ȡ
	vector<int> clickedLinks;//������������Ǵ����������ڼ�����ͨ��father��ȡ
public:
	explicit ListScene(QWidget* parent = 0);
	~ListScene();

public slots:
	void openUrl(QString);

signals:
	void toPage(QString str);//��ʾ���ļ���
	void toInput();			//��ת��������棬����������
};

#endif 