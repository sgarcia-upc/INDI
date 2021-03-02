/********************************************************************************
** Form generated from reading UI file 'Form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *widget;
    QVBoxLayout *All;
    QHBoxLayout *MinutesAndHourLayout;
    QVBoxLayout *HourLayout;
    QLabel *LabelMinutes;
    QLCDNumber *lcdNumber_3;
    QDial *HourDial;
    QVBoxLayout *MinutesLayout;
    QLabel *label_2;
    QLCDNumber *lcdNumber_2;
    QDial *MinuteDial;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(317, 257);
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 11, 301, 241));
        All = new QVBoxLayout(widget);
        All->setObjectName(QString::fromUtf8("All"));
        All->setContentsMargins(0, 0, 0, 0);
        MinutesAndHourLayout = new QHBoxLayout();
        MinutesAndHourLayout->setObjectName(QString::fromUtf8("MinutesAndHourLayout"));
        HourLayout = new QVBoxLayout();
        HourLayout->setObjectName(QString::fromUtf8("HourLayout"));
        LabelMinutes = new QLabel(widget);
        LabelMinutes->setObjectName(QString::fromUtf8("LabelMinutes"));

        HourLayout->addWidget(LabelMinutes);

        lcdNumber_3 = new QLCDNumber(widget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setEnabled(true);

        HourLayout->addWidget(lcdNumber_3);

        HourDial = new QDial(widget);
        HourDial->setObjectName(QString::fromUtf8("HourDial"));
        HourDial->setMaximum(23);

        HourLayout->addWidget(HourDial);

        HourLayout->setStretch(1, 3);
        HourLayout->setStretch(2, 4);

        MinutesAndHourLayout->addLayout(HourLayout);

        MinutesLayout = new QVBoxLayout();
        MinutesLayout->setObjectName(QString::fromUtf8("MinutesLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        MinutesLayout->addWidget(label_2);

        lcdNumber_2 = new QLCDNumber(widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setEnabled(true);

        MinutesLayout->addWidget(lcdNumber_2);

        MinuteDial = new QDial(widget);
        MinuteDial->setObjectName(QString::fromUtf8("MinuteDial"));
        MinuteDial->setMaximum(59);

        MinutesLayout->addWidget(MinuteDial);

        MinutesLayout->setStretch(1, 3);
        MinutesLayout->setStretch(2, 4);

        MinutesAndHourLayout->addLayout(MinutesLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        MinutesAndHourLayout->addItem(horizontalSpacer_2);


        All->addLayout(MinutesAndHourLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        All->addLayout(horizontalLayout_3);


        retranslateUi(Form);
        QObject::connect(pushButton, SIGNAL(clicked()), Form, SLOT(close()));
        QObject::connect(MinuteDial, SIGNAL(sliderMoved(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(HourDial, SIGNAL(sliderMoved(int)), lcdNumber_3, SLOT(display(int)));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        LabelMinutes->setText(QCoreApplication::translate("Form", "Minutes", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Minutes", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
