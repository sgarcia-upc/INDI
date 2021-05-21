/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *reseEscena;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QRadioButton *radioPrincipal;
    QRadioButton *RadioSecondaria;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QDial *Patricio1Dial;
    QLabel *label_3;
    QDial *patricio2Dial;
    QSpacerItem *verticalSpacer;
    QPushButton *Sortir;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(841, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        reseEscena = new QPushButton(MyForm);
        reseEscena->setObjectName(QString::fromUtf8("reseEscena"));

        verticalLayout_2->addWidget(reseEscena);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        radioPrincipal = new QRadioButton(MyForm);
        radioPrincipal->setObjectName(QString::fromUtf8("radioPrincipal"));
        radioPrincipal->setEnabled(true);
        radioPrincipal->setChecked(true);

        verticalLayout_2->addWidget(radioPrincipal);

        RadioSecondaria = new QRadioButton(MyForm);
        RadioSecondaria->setObjectName(QString::fromUtf8("RadioSecondaria"));

        verticalLayout_2->addWidget(RadioSecondaria);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        Patricio1Dial = new QDial(MyForm);
        Patricio1Dial->setObjectName(QString::fromUtf8("Patricio1Dial"));
        Patricio1Dial->setLayoutDirection(Qt::LeftToRight);
        Patricio1Dial->setMinimum(1);
        Patricio1Dial->setMaximum(12);
        Patricio1Dial->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Patricio1Dial);

        label_3 = new QLabel(MyForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        patricio2Dial = new QDial(MyForm);
        patricio2Dial->setObjectName(QString::fromUtf8("patricio2Dial"));
        patricio2Dial->setLayoutDirection(Qt::RightToLeft);
        patricio2Dial->setMaximum(11);
        patricio2Dial->setInvertedAppearance(true);
        patricio2Dial->setInvertedControls(false);

        verticalLayout_2->addWidget(patricio2Dial);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        Sortir = new QPushButton(MyForm);
        Sortir->setObjectName(QString::fromUtf8("Sortir"));

        verticalLayout_2->addWidget(Sortir);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(Sortir, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(reseEscena, SIGNAL(pressed()), widget, SLOT(resetEscena()));
        QObject::connect(radioPrincipal, SIGNAL(clicked()), widget, SLOT(principalCamera()));
        QObject::connect(RadioSecondaria, SIGNAL(clicked()), widget, SLOT(secondaryCamera()));
        QObject::connect(Patricio1Dial, SIGNAL(valueChanged(int)), widget, SLOT(rotpat1(int)));
        QObject::connect(patricio2Dial, SIGNAL(valueChanged(int)), widget, SLOT(rotpat2(int)));
        QObject::connect(widget, SIGNAL(cameraSecondariaRadio(bool)), RadioSecondaria, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(cameraPrincipalRadio(bool)), radioPrincipal, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(dialpatri1(int)), Patricio1Dial, SLOT(setValue(int)));
        QObject::connect(widget, SIGNAL(dialpatri2(int)), patricio2Dial, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        reseEscena->setText(QCoreApplication::translate("MyForm", "resetEscena", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Posicio de la camara:", nullptr));
        radioPrincipal->setText(QCoreApplication::translate("MyForm", "Principal", nullptr));
        RadioSecondaria->setText(QCoreApplication::translate("MyForm", "Secondaria", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Rotacio Patricio 1", nullptr));
#if QT_CONFIG(accessibility)
        Patricio1Dial->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        label_3->setText(QCoreApplication::translate("MyForm", "Rotacio patricio 2", nullptr));
        Sortir->setText(QCoreApplication::translate("MyForm", "Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
