#include "cadastro_de_fornecedores.h"
#include "ui_cadastro_de_fornecedores.h"
#include "janela_principal.h"
#include "variaveis_globais.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_de_fornecedores::cadastro_de_fornecedores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_de_fornecedores)
{
    ui->setupUi(this);

    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
}

cadastro_de_fornecedores::~cadastro_de_fornecedores()
{
    delete ui;
}

void cadastro_de_fornecedores::on_btn_salvar_forn_clicked()
{
    QString nome_fantasia=ui->txt_cad_nome_fantasia->text();
    QString cnpj=ui->txt_cad_cnpj->text();
    QString razao_social=ui->txt_cad_razao_social->text();
    QString cep=ui->txt_cad_cep->text();
    QString bairro=ui->txt_cad_bairro->text();
    QString endereco=ui->txt_cad_endereco->text();
    QString numero=ui->txt_cad_numero->text();
    QString cidade=ui->txt_cad_cidade->text();
    QString nome_cont_forn=ui->txt_cad_cont_nome->text();
    QString dep=ui->txt_cad_cont_dep->text();
    QString fone=ui->txt_cad_cont_tel->text();
    QString ramal=ui->txt_cad_cont_ram->text();
    QString email=ui->txt_cad_cont_email->text();

    QSqlQuery query;
    query.prepare("insert into cadastro_fornecedores (nome_fantasia,"
" cnpj,razao_social,cep,bairro,endereco,numero,cidade,contato_fornecedor,"
" contato_telefone,contato_ramal,contato_email,contato_departamento) values ('"+nome_fantasia+"','"+cnpj+"', "
" '"+razao_social+"','"+cep+"','"+bairro+"','"+endereco+"','"+numero+"','"+cidade+"', "
" '"+nome_cont_forn+"','"+dep+"','"+fone+"','"+ramal+"','"+email+"' ) ");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar fornecedor!");
    }else{
        QMessageBox::warning(this,"OK","Fornecedor cadastrado com sucesso!");
    }
}

void cadastro_de_fornecedores::on_btn_novo_fornecedor_clicked()
{
    ui->txt_cad_nome_fantasia->clear();
    ui->txt_cad_cnpj->clear();
    ui->txt_cad_razao_social->clear();
    ui->txt_cad_cep->clear();
    ui->txt_cad_bairro->clear();
    ui->txt_cad_endereco->clear();
    ui->txt_cad_numero->clear();
    ui->txt_cad_cidade->clear();
    ui->txt_cad_cont_nome->clear();
    ui->txt_cad_cont_dep->clear();
    ui->txt_cad_cont_tel->clear();
    ui->txt_cad_cont_ram->clear();
    ui->txt_cad_cont_email->clear();
    ui->txt_cad_nome_fantasia->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_nome_fantasia_returnPressed()
{
    ui->txt_cad_cnpj->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cnpj_returnPressed()
{
    ui->txt_cad_razao_social->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_razao_social_returnPressed()
{
    ui->txt_cad_cep->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cep_returnPressed()
{
    ui->txt_cad_bairro->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_bairro_returnPressed()
{
    ui->txt_cad_endereco->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_endereco_returnPressed()
{
    ui->txt_cad_numero->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_numero_returnPressed()
{
    ui->txt_cad_cidade->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cidade_returnPressed()
{
    ui->txt_cad_cont_nome->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cont_nome_returnPressed()
{
    ui->txt_cad_cont_tel->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cont_tel_returnPressed()
{
    ui->txt_cad_cont_ram->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cont_ram_returnPressed()
{
    ui->txt_cad_cont_email->setFocus();
}

void cadastro_de_fornecedores::on_txt_cad_cont_email_returnPressed()
{
    ui->txt_cad_cont_dep->setFocus();
}
