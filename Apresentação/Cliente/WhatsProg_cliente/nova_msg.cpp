#include "nova_msg.h"
#include "ui_nova_msg.h"
#include "dados_whatsprog.h"

nova_msg::nova_msg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nova_msg)
{
    ui->setupUi(this);
}

nova_msg::~nova_msg()
{
    delete ui;
}

void nova_msg::setNova()
{
    setWindowTitle("Nova mensagem");
    ui->lineEditDestinatario->clear();
    show();
}

void nova_msg::on_buttonBox_accepted()
{
    string dest = ui->lineEditDestinatario->text().toStdString();
    emit aceitaDestinatario(dest);
}
