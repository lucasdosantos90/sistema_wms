#ifndef CADASTRO_ESTOQUE_H
#define CADASTRO_ESTOQUE_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_estoque;
}

class cadastro_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_estoque(QWidget *parent = nullptr);
    ~cadastro_estoque();
    Conexao con;

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_btn_cad_estoque_clicked();

private:
    Ui::cadastro_estoque *ui;
};

#endif // CADASTRO_ESTOQUE_H
