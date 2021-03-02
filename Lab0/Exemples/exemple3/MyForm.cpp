#include "MyForm.h"
#include <QDebug>
MyForm::MyForm(QWidget* parent):QWidget(parent)
{
	ui.setupUi(this);
}

void MyForm::on_spnAlsada_valueChanged(int arg1)
{
    qDebug() << "Current value is:" << arg1;
}
