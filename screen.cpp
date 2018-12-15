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

//有多少个文件已经被解析
void Screen::handleProcessed(int value) {
	if (value == -1) {//解析完成
		delete ui.progressBar;
		return;
	}
	ui.progressBar->setValue(value);
}

void Screen::startExtract()//开始解析文件的进程
{
	Extractor* extractor = new Extractor(this);
	connect(extractor, SIGNAL(extracted(int)), this, SLOT(handleProcessed(int)));
	extractor->start();
}

Screen::~Screen() {

}