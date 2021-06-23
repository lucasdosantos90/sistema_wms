#ifndef CADASTRO_DE_CLIENTES_H
#define CADASTRO_DE_CLIENTES_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_de_clientes;
}

class cadastro_de_clientes : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_de_clientes(QWidget *parent = nullptr);
    ~cadastro_de_clientes();
    Conexao con;

private slots:
    void on_btn_novo_cliente_clicked();

    void on_btn_salvar_cliente_clicked();

    void on_txt_cad_nome_fantasia_cli_returnPressed();

    void on_txt_cad_cnpj_cli_returnPressed();

    void on_txt_cad_razao_social_cli_returnPressed();

    void on_txt_cad_cep_cli_returnPressed();

    void on_txt_cad_bairro_cli_returnPressed();

    void on_txt_cad_endereco_cli_returnPressed();

    void on_txt_cad_numero_cli_returnPressed();

    void on_txt_cad_cidade_cli_returnPressed();

    void on_txt_cad_cont_nome_cli_returnPressed();

    void on_txt_cad_cont_tel_cli_returnPressed();

    void on_txt_cad_cont_ram_cli_returnPressed();

    void on_txt_cad_cont_email_cli_returnPressed();

private:
    Ui::cadastro_de_clientes *ui;
};

#endif // CADASTRO_DE_CLIENTES_H
