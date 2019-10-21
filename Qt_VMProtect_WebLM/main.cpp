#include "qt_vmprotect_weblm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qt_VMProtect_WebLM w;
	w.show();
	return a.exec();
}
