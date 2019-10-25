#include "qt_vmprotect_weblm.h"
#include "activationform.h"
#include <QtWidgets/QApplication>

bool activate()
{
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, "QtVMP_Demo", "Config");

	struct Options {
		QString key;
		QString serial;
	};
	Options options;

	settings.beginGroup("Settings");
	options.key = settings.value("key", "").toString();
	options.serial = settings.value("serial", "").toString();
	settings.endGroup();
	QString serial = options.serial;
	QString activationKey = options.key;
	DWORD result = 0;

	if (!activationKey.isEmpty() && !serial.isEmpty())
	{
		if ((result = VMProtectActivateLicense(activationKey.toLocal8Bit().data(), serial.toLocal8Bit().data(), 5000)) != 0)
		{
			return false;
		}
		if ((result = VMProtectSetSerialNumber(serial.toLocal8Bit().data())) != 0)
		{
			return false;
		}
		return true;
	}

	return false;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (activate() == true)
	{
		// main window
		Qt_VMProtect_WebLM w;
		w.show();
		return a.exec();
	}
	else {
		// activation window
		ActivationForm activate;
		activate.show();
		return a.exec();
	}

}
