#include "qt_vmprotect_weblm.h"
#include "activationform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Qt_VMProtect_WebLM w;
	w.show();

	ActivationForm activate;
	activate.show();

	return a.exec();
}
