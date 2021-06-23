#ifndef PEDIDO_DE_COMPRA_H
#define PEDIDO_DE_COMPRA_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class pedido_de_compra;
}

class pedido_de_compra : public QDialog
{
    Q_OBJECT

public:
    explicit pedido_de_compra(QWidget *parent = nullptr);
    ~pedido_de_compra();
    Conexao con;

private slots:

    void on_txt_cod_cli_returnPressed();

    void on_rb_cod_cli_clicked();

    void on_rb_nome_cli_clicked();

    void on_rb_cnpj_clicked();

    void on_rb_entrega_retirar_clicked();

    void on_rb_entrega_frete_clicked();

    void on_txt_cod_transp_returnPressed();

    void on_txt_prod_cod_returnPressed();

    void on_txt_valor_desconto_returnPressed();

    void on_rb_tipo_desc_moeda_clicked();

    void on_rb_tipo_desc_porcent_clicked();

    void on_btn_item_add_clicked();

    void on_btn_finalizar_ped_clicked();

    void on_btn_item_excluir_clicked();

    void on_btn_item_edit_clicked();

    void on_btn_novo_ped_clicked();

    void on_txt_prod_qtde_returnPressed();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::pedido_de_compra *ui;
};

#endif // PEDIDO_DE_COMPRA_H
