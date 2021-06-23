#ifndef SEPARACAO_DE_PEDIDOS_H
#define SEPARACAO_DE_PEDIDOS_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class separacao_de_pedidos;
}

class separacao_de_pedidos : public QDialog
{
    Q_OBJECT

public:
    explicit separacao_de_pedidos(QWidget *parent = nullptr);
    ~separacao_de_pedidos();
    Conexao con;

private slots:
    void on_txt_ped_num_returnPressed();

    void on_btn_proximo_clicked();

    void on_btn_anterior_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_txt_ped_cod_produto_returnPressed();

    void on_txt_ped_item_qtde_returnPressed();

private:
    Ui::separacao_de_pedidos *ui;
};

#endif // SEPARACAO_DE_PEDIDOS_H
