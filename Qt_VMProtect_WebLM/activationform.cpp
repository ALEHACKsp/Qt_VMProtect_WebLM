#include "activationform.h"
#include <QMessageBox>
#include <QDebug>

ActivationForm::ActivationForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// hwid textedit
	int nSize = VMProtectGetCurrentHWID(NULL, 0);
	char* p = new char[nSize];
	VMProtectGetCurrentHWID(p, nSize);
	ui.identifier->setText(p);
}

ActivationForm::~ActivationForm()
{
}

void ActivationForm::ParseStatus(int nStatus)
{
	qDebug() <<  "VMProtectSetSerialNumber() returned: " << nStatus << "\r\n";

	int nStatus2 = VMProtectGetSerialNumberState();
	qDebug() << "VMProtectGetSerialNumberState() returned: " << nStatus2 << "\r\n";

	VMProtectSerialNumberData sd = { 0 };
	BOOL res = VMProtectGetSerialNumberData(&sd, sizeof(sd));
	qDebug() << "VMProtectGetSerialNumberData() returned: " << res << "\r\n";

	if (res)
	{
		qDebug() << "State: " << sd.nState << "\r\n";
		qDebug() << "User Name: " << sd.wUserName << "\r\n";
		qDebug() << "E-Mail: " << sd.wEMail << "\r\n";
		qDebug() << "Date of expiration: " << sd.dtExpire.wYear << "-" << sd.dtExpire.bMonth << "-" << sd.dtExpire.bDay << "\r\n";
		qDebug() << "Max date of build: " << sd.dtMaxBuild.wYear << "-" << sd.dtMaxBuild.bMonth << "-" << sd.dtMaxBuild.bDay << "\r\n";
		qDebug() << "Running time limit: " << sd.bRunningTime << "\r\n";
		qDebug() << "Length of user data: " << sd.nUserDataLength << " bytes\r\n";
	}
}
void ActivationForm::ProcessSerialNumber(const char* serial)
{
	int nStatus = VMProtectSetSerialNumber(serial);

	ParseStatus(nStatus);
}

void ActivationForm::ActivateLicense()
{
	char serial[1024];
	int res = VMProtectActivateLicense(ui.textEdit_key->toPlainText().toLocal8Bit(), serial, sizeof(serial));
	switch (res) {
	case ACTIVATION_OK:
		QMessageBox::information(this, "ACTIVATION_OK", "ACTIVATION OK");
		ProcessSerialNumber((const char*)serial);
		break;
	case ACTIVATION_SMALL_BUFFER:
		QMessageBox::information(this, "ACTIVATION_SMALL_BUFFER", "Activation Error");
		break;
	case ACTIVATION_NO_CONNECTION:
		QMessageBox::information(this, "ACTIVATION_NO_CONNECTION", "Activation Error");
		break;
	case ACTIVATION_BAD_REPLY:
		QMessageBox::information(this, "ACTIVATION_BAD_REPLY", "Activation Error");
		break;
	case ACTIVATION_BANNED:
		QMessageBox::information(this, "ACTIVATION_BANNED", "Activation Error");
		break;
	case ACTIVATION_CORRUPTED:
		QMessageBox::information(this, "ACTIVATION_CORRUPTED", "Activation Error");
		break;
	case ACTIVATION_BAD_CODE:
		QMessageBox::information(this, "ACTIVATION_BAD_CODE", "Activation Error");
		break;
	case ACTIVATION_ALREADY_USED:
		QMessageBox::information(this, "ACTIVATION_ALREADY_USED", "Activation Error");
		break;
	case ACTIVATION_SERIAL_UNKNOWN:
		QMessageBox::information(this, "ACTIVATION_SERIAL_UNKNOWN", "Activation Error");
		break;
	case ACTIVATION_EXPIRED:
		QMessageBox::information(this, "ACTIVATION_EXPIRED", "Activation Error");
		break;
	case ACTIVATION_NOT_AVAILABLE:
		QMessageBox::information(this, "ACTIVATION_NOT_AVAILABLE", "Activation Error");
		break;
	}
}

void ActivationForm::on_push_register_clicked()
{
	ActivateLicense();
}

void ActivationForm::on_push_exit_clicked()
{
#if defined(_WIN32)
	TerminateProcess(GetCurrentProcess(), 0);
#endif
#if defined(Q_OS_LINUX)
	qint64 pid = QCoreApplication::applicationPid();
	QProcess::startDetached("kill -9 " + QString::number(pid));
#endif
}
