/********************************************************************************
** Form generated from reading UI file 'list.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIST_H
#define UI_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_List
{
public:

    void setupUi(QWidget *List)
    {
        if (List->objectName().isEmpty())
            List->setObjectName(QStringLiteral("List"));
        List->resize(800, 600);
        List->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255)"));

        retranslateUi(List);

        QMetaObject::connectSlotsByName(List);
    } // setupUi

    void retranslateUi(QWidget *List)
    {
        List->setWindowTitle(QApplication::translate("List", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class List: public Ui_List {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIST_H
