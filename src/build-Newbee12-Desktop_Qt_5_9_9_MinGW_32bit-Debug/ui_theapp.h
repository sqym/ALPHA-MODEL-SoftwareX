/********************************************************************************
** Form generated from reading UI file 'theapp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEAPP_H
#define UI_THEAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_theapp
{
public:

    void setupUi(QWidget *theapp)
    {
        if (theapp->objectName().isEmpty())
            theapp->setObjectName(QStringLiteral("theapp"));
        theapp->resize(800, 600);

        retranslateUi(theapp);

        QMetaObject::connectSlotsByName(theapp);
    } // setupUi

    void retranslateUi(QWidget *theapp)
    {
        theapp->setWindowTitle(QApplication::translate("theapp", "theapp", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class theapp: public Ui_theapp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEAPP_H
