#ifndef CADASTRO_PRODUTOS_H
#define CADASTRO_PRODUTOS_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_produtos;
}

class cadastro_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_produtos(QWidget *parent = nullptr);
    ~cadastro_produtos();
    Conexao con;

private slots:
    void on_btn_cadprod_clicked();

private:
    Ui::cadastro_produtos *ui;
};

#endif // CADASTRO_PRODUTOS_H
