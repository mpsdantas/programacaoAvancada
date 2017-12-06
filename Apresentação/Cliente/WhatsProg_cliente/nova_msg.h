#ifndef NOVA_MSG_H
#define NOVA_MSG_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class nova_msg;
}

class nova_msg : public QDialog
{
    Q_OBJECT

public:
    explicit nova_msg(QWidget *parent = 0);
    void setNova();
    ~nova_msg();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::nova_msg *ui;

signals:
    void aceitaDestinatario(const string &dest);
};

#endif // NOVA_MSG_H
