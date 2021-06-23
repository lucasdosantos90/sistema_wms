#ifndef CADASTRO_DE_TRANSPORTADORAS_H
#define CADASTRO_DE_TRANSPORTADORAS_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_de_transportadoras;
}

class cadastro_de_transportadoras : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_de_transportadoras(QWidget *parent = nullptr);
    ~cadastro_de_transportadoras();
    Conexao con;

private slots:
    void on_btn_salvar_transportadora_clicked();

    void on_btn_nova_transportadora_clicked();

    void on_txt_cad_nome_fantasia_tra_returnPressed();

    void on_txt_cad_cnpj_tra_returnPressed();

    void on_txt_cad_razao_social_tra_returnPressed();

    void on_txt_cad_cep_tra_returnPressed();

    void on_txt_cad_bairro_tra_returnPressed();

    void on_txt_cad_endereco_tra_returnPressed();

    void on_txt_cad_numero_tra_returnPressed();

    void on_txt_cad_cidade_tra_returnPressed();

    void on_txt_cad_valor_frete_tra_returnPressed();

    void on_txt_cad_cont_nome_tra_returnPressed();

    void on_txt_cad_cont_tel_tra_returnPressed();

    void on_txt_cad_cont_ram_tra_returnPressed();

    void on_txt_cad_cont_email_tra_returnPressed();

private:
    Ui::cadastro_de_transportadoras *ui;
};

#endif // CADASTRO_DE_TRANSPORTADORAS_H
