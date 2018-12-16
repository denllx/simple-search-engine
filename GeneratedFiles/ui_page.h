/********************************************************************************
** Form generated from reading UI file 'page.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page
{
public:
    QWebEngineView *webEngineView;
    QLabel *label;

    void setupUi(QWidget *Page)
    {
        if (Page->objectName().isEmpty())
            Page->setObjectName(QStringLiteral("Page"));
        Page->resize(1100, 800);
        Page->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255)"));
        webEngineView = new QWebEngineView(Page);
        webEngineView->setObjectName(QStringLiteral("webEngineView"));
        webEngineView->setGeometry(QRect(10, 10, 821, 781));
        webEngineView->setUrl(QUrl(QStringLiteral("about:blank")));
        label = new QLabel(Page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(920, 40, 131, 71));

        retranslateUi(Page);

        QMetaObject::connectSlotsByName(Page);
    } // setupUi

    void retranslateUi(QWidget *Page)
    {
        Page->setWindowTitle(QApplication::translate("Page", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Page", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#0000ff;\">\347\233\270\345\205\263\346\216\250\350\215\220</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Page: public Ui_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_H
