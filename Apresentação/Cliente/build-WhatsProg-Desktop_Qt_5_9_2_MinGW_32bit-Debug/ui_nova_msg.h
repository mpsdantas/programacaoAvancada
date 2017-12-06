/********************************************************************************
** Form generated from reading UI file 'nova_msg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVA_MSG_H
#define UI_NOVA_MSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_nova_msg
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelDestinatario;
    QLineEdit *lineEditDestinatario;

    void setupUi(QDialog *nova_msg)
    {
        if (nova_msg->objectName().isEmpty())
            nova_msg->setObjectName(QStringLiteral("nova_msg"));
        nova_msg->resize(263, 102);
        buttonBox = new QDialogButtonBox(nova_msg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(60, 50, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelDestinatario = new QLabel(nova_msg);
        labelDestinatario->setObjectName(QStringLiteral("labelDestinatario"));
        labelDestinatario->setGeometry(QRect(30, 20, 71, 20));
        QFont font;
        font.setPointSize(9);
        labelDestinatario->setFont(font);
        lineEditDestinatario = new QLineEdit(nova_msg);
        lineEditDestinatario->setObjectName(QStringLiteral("lineEditDestinatario"));
        lineEditDestinatario->setGeometry(QRect(110, 20, 113, 20));

        retranslateUi(nova_msg);
        QObject::connect(buttonBox, SIGNAL(accepted()), nova_msg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), nova_msg, SLOT(reject()));

        QMetaObject::connectSlotsByName(nova_msg);
    } // setupUi

    void retranslateUi(QDialog *nova_msg)
    {
        nova_msg->setWindowTitle(QApplication::translate("nova_msg", "Dialog", Q_NULLPTR));
        labelDestinatario->setText(QApplication::translate("nova_msg", "Destinat\303\241rio:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class nova_msg: public Ui_nova_msg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVA_MSG_H
