#ifndef JANELA_LOGIN_H
#define JANELA_LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class janela_login;
}

class janela_login : public QDialog
{
    Q_OBJECT

public:
    explicit janela_login(QWidget *parent = nullptr);
    ~janela_login();
    Conexao con;

private slots:
    void on_btn_login_clicked();

private:
    Ui::janela_login *ui;
};

#endif // JANELA_LOGIN_H
