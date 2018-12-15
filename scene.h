#ifndef INPUTS
#define INPUTS
#include <QLabel>
#include <QPushButton>
#include "ui_input.h"

/*
	3������
	1�������û�����
	2��������������б�
	3�������ת���������
*/

class Screen;

class Scene :public QLabel {
	Q_OBJECT

public:
	explicit Scene(QWidget* parent = 0);
	Screen* father;
};

//��������
class InputScene :public Scene {
	Q_OBJECT 

private:
	QPushButton* button;
	Ui::Form* ui;//�����û�����
	QString words;//�����ԭʼ�ַ�
public:
	explicit InputScene(QWidget* parent = 0);
	~InputScene();

public slots:
	void changeWords(const QString& text);//�û����뷢���仯
	void sendWords();//���û�������ִ�

signals:
	void confirmed(char*);//���ִʽ�����͸�Screen����query1
};

#endif 