#ifndef ENTRADA_PRODUTOS_ESTOQUE_H
#define ENTRADA_PRODUTOS_ESTOQUE_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class entrada_produtos_estoque;
}

class entrada_produtos_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit entrada_produtos_estoque(QWidget *parent = nullptr);
    ~entrada_produtos_estoque();
    Conexao con;
private slots:
    void on_txt_estoq_origem_returnPressed();

    void on_txt_estoq_destino_returnPressed();

    void on_txt_loc_origem_returnPressed();

    void on_txt_loc_destino_returnPressed();

    void on_txt_cod_produto_returnPressed();

    void on_txt_qtde_produto_returnPressed();

    void on_btn_add_produtos_clicked();

    void on_btn_nova_transferencia_clicked();

    void on_btn_transferir_clicked();

private:
    Ui::entrada_produtos_estoque *ui;
};

#endif // ENTRADA_PRODUTOS_ESTOQUE_H
