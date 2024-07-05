#include "hoyolabdesktop.h"
#include <QtWidgets/QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	HoYoLABDesktop w;
	w.show();
	return a.exec();
}