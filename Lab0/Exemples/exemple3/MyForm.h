#include "ui_FormAlsada.h"
class MyForm:public QWidget {
	Q_OBJECT
	
	public:
		MyForm(QWidget *parent=0);

private slots:
        void on_spnAlsada_valueChanged(int arg1);

private:
		Ui::Form ui;
};
