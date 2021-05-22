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
#include <QtWidgets/QCheckBox>
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
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
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
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        radioButton_4 = new QRadioButton(MyForm);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setChecked(false);

        verticalLayout->addWidget(radioButton_4);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(MyForm);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(MyForm);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setChecked(true);

        verticalLayout->addWidget(radioButton_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        checkBox = new QCheckBox(MyForm);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(radioButton_4, SIGNAL(clicked()), widget, SLOT(allOff()));
        QObject::connect(radioButton, SIGNAL(clicked()), widget, SLOT(oneOn()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), widget, SLOT(twoOn()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), widget, SLOT(allOn()));
        QObject::connect(widget, SIGNAL(allOff(bool)), radioButton_4, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(oneOn(bool)), radioButton, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(twoOn(bool)), radioButton_2, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(allOn(bool)), radioButton_3, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(reactorSig(bool)), checkBox, SLOT(setChecked(bool)));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), widget, SLOT(reactor(bool)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Control de llums:", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MyForm", "Totes apagades", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "1 encesa", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "2 encesa", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MyForm", "Totes enceses", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Reactor:", nullptr));
        checkBox->setText(QCoreApplication::translate("MyForm", "enc\303\250s", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
