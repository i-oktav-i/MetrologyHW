#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MetrologyHW.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <vector>

using namespace std;

class MetrologyHW : public QMainWindow
{
	Q_OBJECT

public:
	MetrologyHW(QWidget *parent = Q_NULLPTR);

private:
	Ui::MetrologyHWClass ui;

	QLabel lableArr[8];
	QLineEdit fileInPath, fileOutPath;
	QPushButton browseFileIn, browseFileOut, startBtn;
	QString fileInName, fileOutName;

	double normF(double, double, double);

private slots:
	void on_browseFileIn_clicked();
	void on_browseFileOut_clicked();
	void on_startBtn_clicked();
};
