#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void setUsuario(bool Novo);    

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoginDialog *ui;
    bool novoUsuario;

signals:
    void aceitaUsuario(const string &IP, const string &login, const string &senha, bool novoUsuario);
};

#endif // LOGINDIALOG_H
