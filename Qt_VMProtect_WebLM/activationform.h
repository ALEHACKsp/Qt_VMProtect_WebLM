#pragma once

#include <QWidget>
#include "ui_activationform.h"

class ActivationForm : public QWidget
{
	Q_OBJECT

public:
	ActivationForm(QWidget *parent = Q_NULLPTR);
	~ActivationForm();

private:
	Ui::ActivationForm ui;
};
