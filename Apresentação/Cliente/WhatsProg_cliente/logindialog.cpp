#include "logindialog.h"
#include "ui_logindialog.h"
#include "dados_whatsprog.h"
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    novoUsuario(false)
{
    ui->setupUi(this);

    ui->lineEditSenhaUsuario->setEchoMode( QLineEdit::Password );
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setUsuario(bool NovoUsuario)
{
    novoUsuario = NovoUsuario;
    setWindowTitle(novoUsuario ? "Usuário - Criar" :
                                 "Usuário - Conectar");
    ui->lineEditIpServidor->clear();
    ui->lineEditNomeUsuario->clear();
    ui->lineEditSenhaUsuario->clear();
    ui->lineEditIpServidor->setText("192.168.0.2");//192.168.0.
    ui->lineEditNomeUsuario->setText("rodrigo");
    ui->lineEditSenhaUsuario->setText("rodrigo");
    show();
}

void LoginDialog::on_buttonBox_accepted()
{
    string IP = ui->lineEditIpServidor->text().toStdString();
    string login = ui->lineEditNomeUsuario->text().toStdString();
    string senha = ui->lineEditSenhaUsuario->text().toStdString();

    emit aceitaUsuario( IP, login, senha, novoUsuario );
}
