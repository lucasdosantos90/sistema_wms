#include "cadastro_de_transportadoras.h"
#include "ui_cadastro_de_transportadoras.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_de_transportadoras::cadastro_de_transportadoras(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_de_transportadoras)
{
    ui->setupUi(this);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
}

cadastro_de_transportadoras::~cadastro_de_transportadoras()
{
    delete ui;
}

void cadastro_de_transportadoras::on_btn_salvar_transportadora_clicked()
{
    QString nome_fantasia=ui->txt_cad_nome_fantasia_tra->text();
    QString cnpj=ui->txt_cad_cnpj_tra->text();
    QString razao_social=ui->txt_cad_razao_social_tra->text();
    QString cep=ui->txt_cad_cep_tra->text();
    QString bairro=ui->txt_cad_bairro_tra->text();
    QString endereco=ui->txt_cad_endereco_tra->text();
    QString numero=ui->txt_cad_numero_tra->text();
    QString cidade=ui->txt_cad_cidade_tra->text();
    QString nome_cont_transp=ui->txt_cad_cont_nome_tra->text();
    QString dep=ui->txt_cad_cont_dep_tra->text();
    QString fone=ui->txt_cad_cont_tel_tra->text();
    QString ramal=ui->txt_cad_cont_ram_tra->text();
    QString email=ui->txt_cad_cont_email_tra->text();
    QString aux;

    aux=ui->txt_cad_valor_frete_tra->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_frete=aux;

    QSqlQuery query;
    query.prepare("insert into cadastro_transportadoras (nome_fantasia,"
" cnpj,razao_social,cep,bairro,endereco,numero,cidade,contato_transportadora,"
" contato_telefone,contato_ramal,contato_email,contato_departamento,valor_frete) values ('"+nome_fantasia+"','"+cnpj+"', "
" '"+razao_social+"','"+cep+"','"+bairro+"','"+endereco+"','"+numero+"','"+cidade+"', "
" '"+nome_cont_transp+"','"+dep+"','"+fone+"','"+ramal+"','"+email+"',"+QString::number(valor_frete.toFloat())+" ) ");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar transportadora!");
    }else{
        QMessageBox::warning(this,"OK","Transportadora cadastrada com sucesso!");
    }
}

void cadastro_de_transportadoras::on_btn_nova_transportadora_clicked()
{
    ui->txt_cad_nome_fantasia_tra->clear();
    ui->txt_cad_cnpj_tra->clear();
    ui->txt_cad_razao_social_tra->clear();
    ui->txt_cad_cep_tra->clear();
    ui->txt_cad_bairro_tra->clear();
    ui->txt_cad_endereco_tra->clear();
    ui->txt_cad_numero_tra->clear();
    ui->txt_cad_cidade_tra->clear();
    ui->txt_cad_valor_frete_tra->clear();
    ui->txt_cad_cont_nome_tra->clear();
    ui->txt_cad_cont_tel_tra->clear();
    ui->txt_cad_cont_ram_tra->clear();
    ui->txt_cad_cont_email_tra->clear();
    ui->txt_cad_cont_dep_tra->clear();
    ui->txt_cad_nome_fantasia_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_nome_fantasia_tra_returnPressed()
{
    ui->txt_cad_cnpj_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cnpj_tra_returnPressed()
{
    ui->txt_cad_razao_social_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_razao_social_tra_returnPressed()
{
    ui->txt_cad_cep_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cep_tra_returnPressed()
{
    ui->txt_cad_bairro_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_bairro_tra_returnPressed()
{
    ui->txt_cad_endereco_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_endereco_tra_returnPressed()
{
    ui->txt_cad_numero_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_numero_tra_returnPressed()
{
    ui->txt_cad_cidade_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cidade_tra_returnPressed()
{
    ui->txt_cad_valor_frete_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_valor_frete_tra_returnPressed()
{
    ui->txt_cad_cont_nome_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cont_nome_tra_returnPressed()
{
    ui->txt_cad_cont_tel_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cont_tel_tra_returnPressed()
{
    ui->txt_cad_cont_ram_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cont_ram_tra_returnPressed()
{
    ui->txt_cad_cont_email_tra->setFocus();
}

void cadastro_de_transportadoras::on_txt_cad_cont_email_tra_returnPressed()
{
    ui->txt_cad_cont_dep_tra->setFocus();
}
