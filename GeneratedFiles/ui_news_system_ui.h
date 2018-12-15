/********************************************************************************
** Form generated from reading UI file 'news_system_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWS_SYSTEM_UI_H
#define UI_NEWS_SYSTEM_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_news_system_uiClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *news_system_uiClass)
    {
        if (news_system_uiClass->objectName().isEmpty())
            news_system_uiClass->setObjectName(QStringLiteral("news_system_uiClass"));
        news_system_uiClass->resize(600, 400);
        news_system_uiClass->setStyleSheet(QStringLiteral("background-color:rgb(200,128,43)"));
        centralWidget = new QWidget(news_system_uiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color:rgb(200, 128, 43)"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 90, 181, 51));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::AutoText);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(120, 160, 341, 23));
        progressBar->setStyleSheet(QLatin1String("QProgressBar{\n"
"     background:transparent}\n"
"QProgressBar::chunk {\n"
"     background-color: rgb(239, 217, 193)}\n"
""));
        progressBar->setValue(0);
        news_system_uiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(news_system_uiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        news_system_uiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(news_system_uiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        news_system_uiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(news_system_uiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        news_system_uiClass->setStatusBar(statusBar);

        retranslateUi(news_system_uiClass);

        QMetaObject::connectSlotsByName(news_system_uiClass);
    } // setupUi

    void retranslateUi(QMainWindow *news_system_uiClass)
    {
        news_system_uiClass->setWindowTitle(QApplication::translate("news_system_uiClass", "news_system_ui", Q_NULLPTR));
        label->setText(QApplication::translate("news_system_uiClass", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600; color:#ffffff;\">loading...</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class news_system_uiClass: public Ui_news_system_uiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWS_SYSTEM_UI_H
