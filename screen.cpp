#include "screen.h"
#include "extractor.h"
#include <QTimer>

/*void Screen::changeText() {
	ui.label->setText("clicked!");
}*/

Screen::Screen(QWidget* parent)
	:QMainWindow(parent) {
	ui.setupUi(this);
	//ui.pushButton->setText("hello world!");
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(changeText()));
	QTimer::singleShot(10, this, SLOT(startExtract()));
}

//�ж��ٸ��ļ��Ѿ�������
void Screen::handleProcessed(int value) {
	if (value == -1) {//�������
		delete ui.progressBar;
		return;
	}
	ui.progressBar->setValue(value);
}

void Screen::startExtract()//��ʼ�����ļ��Ľ���
{
	Extractor* extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
}

Screen::~Screen() {

}