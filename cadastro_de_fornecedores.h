#ifndef CADASTRO_DE_FORNECEDORES_H
#define CADASTRO_DE_FORNECEDORES_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_de_fornecedores;
}

class cadastro_de_fornecedores : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_de_fornecedores(QWidget *parent = nullptr);
    ~cadastro_de_fornecedores();
    Conexao con;

private slots:
    void on_btn_salvar_forn_clicked();

    void on_btn_novo_fornecedor_clicked();

    void on_txt_cad_nome_fantasia_returnPressed();

    void on_txt_cad_cnpj_returnPressed();

    void on_txt_cad_razao_social_returnPressed();

    void on_txt_cad_cep_returnPressed();

    void on_txt_cad_bairro_returnPressed();

    void on_txt_cad_endereco_returnPressed();

    void on_txt_cad_numero_returnPressed();

    void on_txt_cad_cidade_returnPressed();

    void on_txt_cad_cont_nome_returnPressed();

    void on_txt_cad_cont_tel_returnPressed();

    void on_txt_cad_cont_ram_returnPressed();

    void on_txt_cad_cont_email_returnPressed();

private:
    Ui::cadastro_de_fornecedores *ui;
};

#endif // CADASTRO_DE_FORNECEDORES_H
