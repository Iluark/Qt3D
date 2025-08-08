/********************************************************************************
** Form generated from reading UI file 'ProcessModelWithQt3D.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSMODELWITHQT3D_H
#define UI_PROCESSMODELWITHQT3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProcessModelWithQt3D
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *model3DViewContainer;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *directionComboBox;
    QPushButton *load3DModelBtn;
    QPushButton *createGrayImage;
    QPushButton *saveGrayImage;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *grayImageLabel;

    void setupUi(QWidget *ProcessModelWithQt3D)
    {
        if (ProcessModelWithQt3D->objectName().isEmpty())
            ProcessModelWithQt3D->setObjectName(QString::fromUtf8("ProcessModelWithQt3D"));
        ProcessModelWithQt3D->resize(783, 615);
        horizontalLayout = new QHBoxLayout(ProcessModelWithQt3D);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        model3DViewContainer = new QWidget(ProcessModelWithQt3D);
        model3DViewContainer->setObjectName(QString::fromUtf8("model3DViewContainer"));

        horizontalLayout->addWidget(model3DViewContainer);

        widget_2 = new QWidget(ProcessModelWithQt3D);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        directionComboBox = new QComboBox(groupBox);
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->setObjectName(QString::fromUtf8("directionComboBox"));
        directionComboBox->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(directionComboBox);


        verticalLayout->addWidget(groupBox);

        load3DModelBtn = new QPushButton(widget_4);
        load3DModelBtn->setObjectName(QString::fromUtf8("load3DModelBtn"));
        load3DModelBtn->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(load3DModelBtn);

        createGrayImage = new QPushButton(widget_4);
        createGrayImage->setObjectName(QString::fromUtf8("createGrayImage"));
        createGrayImage->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(createGrayImage);

        saveGrayImage = new QPushButton(widget_4);
        saveGrayImage->setObjectName(QString::fromUtf8("saveGrayImage"));
        saveGrayImage->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(saveGrayImage);


        verticalLayout_2->addWidget(widget_4);

        frame = new QFrame(widget_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Shape::Box);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        grayImageLabel = new QLabel(frame);
        grayImageLabel->setObjectName(QString::fromUtf8("grayImageLabel"));
        grayImageLabel->setMinimumSize(QSize(237, 305));
        grayImageLabel->setMaximumSize(QSize(237, 305));

        horizontalLayout_4->addWidget(grayImageLabel);


        verticalLayout_2->addWidget(frame);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);

        horizontalLayout->addWidget(widget_2);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(ProcessModelWithQt3D);

        QMetaObject::connectSlotsByName(ProcessModelWithQt3D);
    } // setupUi

    void retranslateUi(QWidget *ProcessModelWithQt3D)
    {
        ProcessModelWithQt3D->setWindowTitle(QCoreApplication::translate("ProcessModelWithQt3D", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ProcessModelWithQt3D", "\346\226\271\345\220\221", nullptr));
        directionComboBox->setItemText(0, QCoreApplication::translate("ProcessModelWithQt3D", "+X", nullptr));
        directionComboBox->setItemText(1, QCoreApplication::translate("ProcessModelWithQt3D", "-X", nullptr));
        directionComboBox->setItemText(2, QCoreApplication::translate("ProcessModelWithQt3D", "+Y", nullptr));
        directionComboBox->setItemText(3, QCoreApplication::translate("ProcessModelWithQt3D", "-Y", nullptr));
        directionComboBox->setItemText(4, QCoreApplication::translate("ProcessModelWithQt3D", "+Z", nullptr));
        directionComboBox->setItemText(5, QCoreApplication::translate("ProcessModelWithQt3D", "-Z", nullptr));
        directionComboBox->setItemText(6, QCoreApplication::translate("ProcessModelWithQt3D", "Origin", nullptr));

        load3DModelBtn->setText(QCoreApplication::translate("ProcessModelWithQt3D", "\350\275\275\345\205\2453D\346\250\241\345\236\213", nullptr));
        createGrayImage->setText(QCoreApplication::translate("ProcessModelWithQt3D", "\347\224\237\346\210\220\347\201\260\345\272\246\345\233\276", nullptr));
        saveGrayImage->setText(QCoreApplication::translate("ProcessModelWithQt3D", "\344\277\235\345\255\230\347\201\260\345\272\246\345\233\276", nullptr));
        grayImageLabel->setText(QCoreApplication::translate("ProcessModelWithQt3D", "image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcessModelWithQt3D: public Ui_ProcessModelWithQt3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESSMODELWITHQT3D_H
