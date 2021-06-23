#include "janela_login.h"
#include "ui_janela_login.h"
#include "ui_janela_principal.h"
#include "janela_principal.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "variaveis_globais.h"


janela_login::janela_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::janela_login)
{
    ui->setupUi(this);
    this->window()->setFixedSize(450,300);
        if(!con.aberto()){
            ui->label_conexao_bd->setText("Sem Conexão!");
        }else{
            ui->label_conexao_bd->setText("Conectado");
        }
        ui->txt_login_username->setText("adm");
        ui->txt_login_senha->setText("123");
}

janela_login::~janela_login()
{
    delete ui;
}

void janela_login::on_btn_login_clicked()
{
    if(!con.abrir()){
        QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
    }else{
        QString username=ui->txt_login_username->text();
        QString senha=ui->txt_login_senha->text();
        QSqlQuery query;
        if(query.exec("select * from tabela_usuarios where username_usuario='"+username+"' and senha_usuario='"+senha+"'")){
            query.first();
            if(query.value(0).toString()!=""){
                QMessageBox::information(this,"OK","Bem Vindo!");
                this->close();

                variaveis_globais::logado=true;
                variaveis_globais::nome=query.value(1).toString();
                variaveis_globais::username=query.value(4).toString();

                QSqlQuery query_acesso;
                query_acesso.exec("select * from acesso_usuarios where username_usuario='"+variaveis_globais::username+"'");
                query_acesso.first();
                variaveis_globais::acesso=query_acesso.value(1).toString();

            }else{
                QMessageBox::warning(this,"Erro","Informações Incorretas!");
                ui->txt_login_senha->setText("");
                ui->txt_login_username->setText("");
                ui->txt_login_username->setFocus();
            }
        }
    }
    con.fechar();
}
