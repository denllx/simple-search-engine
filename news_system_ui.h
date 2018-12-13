#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_news_system_ui.h"

class news_system_ui : public QMainWindow
{
	Q_OBJECT

public:
	news_system_ui(QWidget *parent = Q_NULLPTR);

private:
	Ui::news_system_uiClass ui;
};
