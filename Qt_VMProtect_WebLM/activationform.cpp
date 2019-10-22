#include "activationform.h"

ActivationForm::ActivationForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ActivationForm::~ActivationForm()
{
}

void ActivationForm::on_push_register_clicked()
{

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
