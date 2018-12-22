#include "news_system_ui.h"
#include <QtWidgets/QApplication>
#include <QFontMetrics>
#include "screen.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QFont f("ZYSong18030", 12);
	a.setFont(f);
	Screen w;
	w.show();
	return a.exec();
}

