/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *labelIpServidor;
    QLineEdit *lineEditIpServidor;
    QLabel *labelNomeUsuario;
    QLineEdit *lineEditNomeUsuario;
    QLabel *labelSenhaUsuario;
    QLineEdit *lineEditSenhaUsuario;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(248, 125);
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelIpServidor = new QLabel(LoginDialog);
        labelIpServidor->setObjectName(QStringLiteral("labelIpServidor"));

        gridLayout->addWidget(labelIpServidor, 0, 0, 1, 1);

        lineEditIpServidor = new QLineEdit(LoginDialog);
        lineEditIpServidor->setObjectName(QStringLiteral("lineEditIpServidor"));

        gridLayout->addWidget(lineEditIpServidor, 0, 1, 1, 1);

        labelNomeUsuario = new QLabel(LoginDialog);
        labelNomeUsuario->setObjectName(QStringLiteral("labelNomeUsuario"));

        gridLayout->addWidget(labelNomeUsuario, 1, 0, 1, 1);

        lineEditNomeUsuario = new QLineEdit(LoginDialog);
        lineEditNomeUsuario->setObjectName(QStringLiteral("lineEditNomeUsuario"));

        gridLayout->addWidget(lineEditNomeUsuario, 1, 1, 1, 1);

        labelSenhaUsuario = new QLabel(LoginDialog);
        labelSenhaUsuario->setObjectName(QStringLiteral("labelSenhaUsuario"));

        gridLayout->addWidget(labelSenhaUsuario, 2, 0, 1, 1);

        lineEditSenhaUsuario = new QLineEdit(LoginDialog);
        lineEditSenhaUsuario->setObjectName(QStringLiteral("lineEditSenhaUsuario"));

        gridLayout->addWidget(lineEditSenhaUsuario, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(LoginDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(LoginDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LoginDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LoginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login Usu\303\241rio", Q_NULLPTR));
        labelIpServidor->setText(QApplication::translate("LoginDialog", "Servidor (IP):", Q_NULLPTR));
        labelNomeUsuario->setText(QApplication::translate("LoginDialog", "Usu\303\241rio", Q_NULLPTR));
        labelSenhaUsuario->setText(QApplication::translate("LoginDialog", "Senha", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
