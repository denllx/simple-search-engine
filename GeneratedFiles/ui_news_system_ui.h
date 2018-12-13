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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_news_system_uiClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *news_system_uiClass)
    {
        if (news_system_uiClass->objectName().isEmpty())
            news_system_uiClass->setObjectName(QStringLiteral("news_system_uiClass"));
        news_system_uiClass->resize(600, 400);
        centralWidget = new QWidget(news_system_uiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 100, 93, 28));
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
        pushButton->setText(QApplication::translate("news_system_uiClass", "\347\231\276\345\272\246\346\220\234\347\264\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class news_system_uiClass: public Ui_news_system_uiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWS_SYSTEM_UI_H
