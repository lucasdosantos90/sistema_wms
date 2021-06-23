#include "cadastro_de_clientes.h"
#include "ui_cadastro_de_clientes.h"
#include "variaveis_globais.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_de_clientes::cadastro_de_clientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_de_clientes)
{
    ui->setupUi(this);

    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
}

cadastro_de_clientes::~cadastro_de_clientes()
{
    delete ui;
}

void cadastro_de_clientes::on_btn_novo_cliente_clicked()
{
    ui->txt_cad_nome_fantasia_cli->clear();
    ui->txt_cad_cnpj_cli->clear();
    ui->txt_cad_razao_social_cli->clear();
    ui->txt_cad_cep_cli->clear();
    ui->txt_cad_bairro_cli->clear();
    ui->txt_cad_endereco_cli->clear();
    ui->txt_cad_numero_cli->clear();
    ui->txt_cad_cidade_cli->clear();
    ui->txt_cad_cont_nome_cli->clear();
    ui->txt_cad_cont_dep_cli->clear();
    ui->txt_cad_cont_tel_cli->clear();
    ui->txt_cad_cont_ram_cli->clear();
    ui->txt_cad_cont_email_cli->clear();
    ui->txt_cad_nome_fantasia_cli->setFocus();
}

void cadastro_de_clientes::on_btn_salvar_cliente_clicked()
{
    QString nome_fantasia=ui->txt_cad_nome_fantasia_cli->text();
    QString cnpj=ui->txt_cad_cnpj_cli->text();
    QString razao_social=ui->txt_cad_razao_social_cli->text();
    QString cep=ui->txt_cad_cep_cli->text();
    QString bairro=ui->txt_cad_bairro_cli->text();
    QString endereco=ui->txt_cad_endereco_cli->text();
    QString numero=ui->txt_cad_numero_cli->text();
    QString cidade=ui->txt_cad_cidade_cli->text();
    QString nome_cont_forn=ui->txt_cad_cont_nome_cli->text();
    QString dep=ui->txt_cad_cont_dep_cli->text();
    QString fone=ui->txt_cad_cont_tel_cli->text();
    QString ramal=ui->txt_cad_cont_ram_cli->text();
    QString email=ui->txt_cad_cont_email_cli->text();

    QSqlQuery query;
    query.prepare("insert into cadastro_clientes (nome_fantasia,"
" cnpj,razao_social,cep,bairro,endereco,numero,cidade,contato_fornecedor,"
" contato_telefone,contato_ramal,contato_email,contato_departamento) values ('"+nome_fantasia+"','"+cnpj+"', "
" '"+razao_social+"','"+cep+"','"+bairro+"','"+endereco+"','"+numero+"','"+cidade+"', "
" '"+nome_cont_forn+"','"+dep+"','"+fone+"','"+ramal+"','"+email+"' ) ");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar cliente!");
    }else{
        QMessageBox::warning(this,"OK","Cliente cadastrado com sucesso!");
    }
}

void cadastro_de_clientes::on_txt_cad_nome_fantasia_cli_returnPressed()
{
    ui->txt_cad_cnpj_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cnpj_cli_returnPressed()
{
    ui->txt_cad_razao_social_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_razao_social_cli_returnPressed()
{
    ui->txt_cad_cep_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cep_cli_returnPressed()
{
    ui->txt_cad_bairro_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_bairro_cli_returnPressed()
{
    ui->txt_cad_endereco_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_endereco_cli_returnPressed()
{
    ui->txt_cad_numero_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_numero_cli_returnPressed()
{
    ui->txt_cad_cidade_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cidade_cli_returnPressed()
{
    ui->txt_cad_cont_nome_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cont_nome_cli_returnPressed()
{
    ui->txt_cad_cont_tel_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cont_tel_cli_returnPressed()
{
    ui->txt_cad_cont_ram_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cont_ram_cli_returnPressed()
{
    ui->txt_cad_cont_email_cli->setFocus();
}

void cadastro_de_clientes::on_txt_cad_cont_email_cli_returnPressed()
{
    ui->txt_cad_cont_dep_cli->setFocus();
}
