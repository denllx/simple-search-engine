#ifndef INPUTS
#define INPUTS
#include <QLabel>
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

#endif 