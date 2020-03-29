#include "VRM.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VRM w;
	w.show();
	return a.exec();
}
