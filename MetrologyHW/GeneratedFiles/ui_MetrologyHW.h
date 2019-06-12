/********************************************************************************
** Form generated from reading UI file 'MetrologyHW.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_METROLOGYHW_H
#define UI_METROLOGYHW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MetrologyHWClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MetrologyHWClass)
    {
        if (MetrologyHWClass->objectName().isEmpty())
            MetrologyHWClass->setObjectName(QString::fromUtf8("MetrologyHWClass"));
        MetrologyHWClass->resize(600, 400);
        menuBar = new QMenuBar(MetrologyHWClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MetrologyHWClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MetrologyHWClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MetrologyHWClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MetrologyHWClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MetrologyHWClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MetrologyHWClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MetrologyHWClass->setStatusBar(statusBar);

        retranslateUi(MetrologyHWClass);

        QMetaObject::connectSlotsByName(MetrologyHWClass);
    } // setupUi

    void retranslateUi(QMainWindow *MetrologyHWClass)
    {
        MetrologyHWClass->setWindowTitle(QApplication::translate("MetrologyHWClass", "MetrologyHW", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MetrologyHWClass: public Ui_MetrologyHWClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_METROLOGYHW_H
