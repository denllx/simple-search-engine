#ifndef INPUTSCENE_H
#define INPUTSCENE_H

#include "scene.h"
#include <QLabel>
#include <QPushButton>
#include "ui_input.h"

using namespace Ui;

//��������
class InputScene :public Scene {
	Q_OBJECT

private:
	QPushButton* button;
	Ui::Input* ui;//�����û�����
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
