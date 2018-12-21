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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page
{
public:
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *titlebrowser;
    QTextBrowser *timebrowser;
    QTextBrowser *sourcebrowser;
    QTextBrowser *mainbrowser;
    QPushButton *back;

    void setupUi(QWidget *Page)
    {
        if (Page->objectName().isEmpty())
            Page->setObjectName(QStringLiteral("Page"));
        Page->resize(1100, 800);
        Page->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255)"));
        label = new QLabel(Page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(870, 40, 131, 71));
        verticalLayoutWidget = new QWidget(Page);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 50, 771, 721));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titlebrowser = new QTextBrowser(verticalLayoutWidget);
        titlebrowser->setObjectName(QStringLiteral("titlebrowser"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titlebrowser->sizePolicy().hasHeightForWidth());
        titlebrowser->setSizePolicy(sizePolicy);
        titlebrowser->setMaximumSize(QSize(16777215, 50));
        titlebrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout->addWidget(titlebrowser);

        timebrowser = new QTextBrowser(verticalLayoutWidget);
        timebrowser->setObjectName(QStringLiteral("timebrowser"));
        timebrowser->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(timebrowser);

        sourcebrowser = new QTextBrowser(verticalLayoutWidget);
        sourcebrowser->setObjectName(QStringLiteral("sourcebrowser"));
        sourcebrowser->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(sourcebrowser);

        mainbrowser = new QTextBrowser(verticalLayoutWidget);
        mainbrowser->setObjectName(QStringLiteral("mainbrowser"));

        verticalLayout->addWidget(mainbrowser);

        back = new QPushButton(Page);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(40, 10, 93, 28));

        retranslateUi(Page);

        QMetaObject::connectSlotsByName(Page);
    } // setupUi

    void retranslateUi(QWidget *Page)
    {
        Page->setWindowTitle(QApplication::translate("Page", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Page", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#0000ff;\">\347\233\270\345\205\263\346\220\234\347\264\242</span></p></body></html>", Q_NULLPTR));
        back->setText(QApplication::translate("Page", "\345\220\216\351\200\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Page: public Ui_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_H
