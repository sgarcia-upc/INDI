TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH +=  /home/sgarcia/Programacio/INDI/Lab2.1/models


FORMS += MyForm.ui

HEADERS += MyForm.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        MyGLWidget.cpp 

SOURCES += /home/sgarcia/Programacio/INDI/Lab2.1/models/Model/model.cpp
