#ifndef INPUTS
#define INPUTS
#include <QLabel>
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

#endif 