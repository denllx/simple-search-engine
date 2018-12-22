#include "guiutils.h"

 void elided(QLabel* label,QString& str){
	 QFont font;
	 QFontMetrics fontmetrics(font);
	 QString elidestr = fontmetrics.elidedText(str, Qt::ElideRight, label->width() * 3);
	 label->setText(str);
}