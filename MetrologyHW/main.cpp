#include "MetrologyHW.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MetrologyHW w;
	w.show();
	return a.exec();
}
