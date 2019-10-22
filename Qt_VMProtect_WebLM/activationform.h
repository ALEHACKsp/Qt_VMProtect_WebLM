#pragma once
#include <windows.h>
#include <processthreadsapi.h>
#include <QWidget>
#include "ui_activationform.h"
#include "VMProtectSDK.h"

class ActivationForm : public QWidget
{
	Q_OBJECT

public:
	ActivationForm(QWidget *parent = Q_NULLPTR);
	~ActivationForm();

	void ParseStatus(int nStatus);
	void ProcessSerialNumber(const char* serial);
	void ActivateLicense();
	Ui::ActivationForm ui;
private slots:
	void on_push_register_clicked();
	void on_push_exit_clicked();
};
