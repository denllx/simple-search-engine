#ifndef INPUTSCENE_H
#define INPUTSCENE_H

#include "scene.h"
#include <QLabel>
#include <QPushButton>
#include "ui_input.h"

using namespace Ui;

//搜索界面
class InputScene :public Scene {
	Q_OBJECT

private:
	QPushButton* button;
	Ui::Input* ui;//接收用户输入
	QString words;//输入的原始字符
public:
	explicit InputScene(QWidget* parent = 0);
	~InputScene();

public slots:
	void changeWords(const QString& text);//用户输入发生变化
	void sendWords();//将用户的输入分词

signals:
	void confirmed(char*);//将分词结果发送给Screen进行query1
};

#endif 
