#include "qt_vmprotect_weblm.h"
#include "activationform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// main window
	Qt_VMProtect_WebLM w;
	w.show();

	// activation window
	ActivationForm activate;
	activate.show();

	return a.exec();
}
