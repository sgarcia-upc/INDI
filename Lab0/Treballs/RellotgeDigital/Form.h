#include "ui_Form.h"

class Form:public QWidget {
    Q_OBJECT
    public:
        Form(QWidget * parent=0);
    
    private:
        Ui::Form ui;

};
