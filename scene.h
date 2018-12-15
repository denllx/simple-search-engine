#ifndef INPUTS
#define INPUTS
#include <QLabel>
#include <QPushButton>
#include "ui_input.h"

/*
	3个场景
	1：接收用户输入
	2：返回搜索结果列表
	3：点击跳转到搜索结果
*/

class Screen;

class Scene :public QLabel {
	Q_OBJECT

public:
	explicit Scene(QWidget* parent = 0);
	Screen* father;
};

//搜索界面
class InputScene :public Scene {
	Q_OBJECT 

private:
	QPushButton* button;
	Ui::Form* ui;//接收用户输入
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