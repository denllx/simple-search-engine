/********************************************************************************
** Form generated from reading UI file 'input.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUT_H
#define UI_INPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Input
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *Input)
    {
        if (Input->objectName().isEmpty())
            Input->setObjectName(QStringLiteral("Input"));
        Input->resize(800, 600);
        Input->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255)"));
        lineEdit = new QLineEdit(Input);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(160, 280, 451, 51));
        label = new QLabel(Input);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 220, 251, 41));
        pushButton = new QPushButton(Input);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(610, 280, 93, 51));
        pushButton->setStyleSheet(QStringLiteral("background-color:rgb(0,0,255)"));

        retranslateUi(Input);

        QMetaObject::connectSlotsByName(Input);
    } // setupUi

    void retranslateUi(QWidget *Input)
    {
        Input->setWindowTitle(QApplication::translate("Input", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Input", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600; color:#55aaff;\">\344\270\200\344\270\252\345\276\210\350\217\234\347\232\204\346\220\234\347\264\242\345\274\225\346\223\216</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Input", "\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Input: public Ui_Input {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_H
