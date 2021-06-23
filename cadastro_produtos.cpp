#include "cadastro_produtos.h"
#include "ui_cadastro_produtos.h"
#include "variaveis_globais.h"
#include <QSqlQuery>
#include <QMessageBox>

cadastro_produtos::cadastro_produtos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_produtos)
{
    ui->setupUi(this);

    ui->txt_cad_nomeprod->setFocus();
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
    ui->tableWidget_cad_prod->setColumnCount(5);
    ui->tableWidget_cad_prod->setColumnWidth(0,50);
    ui->tableWidget_cad_prod->setColumnWidth(1,100);
    QStringList cabecalho={"Nome do produto","Descrição",
                       "Usuário que cadastrou","Valor",
                       "Código"};
    ui->tableWidget_cad_prod->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget_cad_prod->setStyleSheet("QTableView {selection-background-color:blue");
    ui->tableWidget_cad_prod->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_cad_prod->verticalHeader()->setVisible(false);
    ui->tableWidget_cad_prod->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_cad_prod->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_cad_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);

    while(ui->tableWidget_cad_prod->rowCount()>0){
        ui->tableWidget_cad_prod->removeRow(0);
    }
    int contlinhas=0;
    QSqlQuery query;
    query.prepare("select nome_produto,descricao_produto,username_usuario_cadastro_produto,"
                  "valor_produto,codigo_produto from cadastro_produtos order by nome_produto");
    if(query.exec()){
        while(query.next()){
            ui->tableWidget_cad_prod->insertRow(contlinhas);
            ui->tableWidget_cad_prod->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_cad_prod->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_cad_prod->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget_cad_prod->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget_cad_prod->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget_cad_prod->setRowHeight(contlinhas,5);
            contlinhas++;
        }
    }else{
        QMessageBox::warning(this,"Erro","Erro ao listar produtos!");
    }
}

cadastro_produtos::~cadastro_produtos()
{
    delete ui;
}

void cadastro_produtos::on_btn_cadprod_clicked()
{
    QString nome_produto=ui->txt_cad_nomeprod->text();
    QString desc_produto=ui->txt_cad_descprod->text();
    QString codigo_produto=ui->txt_cad_codprod->text();
    QString user_cadastrou_prod=variaveis_globais::username;

    QString aux;
    aux=ui->txt_cad_valprod->text();
    std::replace(aux.begin(),aux.end(),',','.');
    QString valor_produto=aux;

    //int contlinhas=0;
    QSqlQuery query;
    query.prepare("insert into cadastro_produtos (nome_produto,descricao_produto,"
                  "username_usuario_cadastro_produto,valor_produto,codigo_produto)"
                  " values ('"+nome_produto+"','"+desc_produto+"','"+user_cadastrou_prod+"',"
                  " "+QString::number(valor_produto.toFloat())+",'"+codigo_produto+"')");
    if(!query.exec()){
        QMessageBox::information(this,"Erro!","Erro ao efetuar cadastro");
    }else{
        QMessageBox::information(this,"Gravado!","Cadastro efetuado com sucesso!");

        while(ui->tableWidget_cad_prod->rowCount()>0){
            ui->tableWidget_cad_prod->removeRow(0);
        }
        int contlinhas=0;
        QSqlQuery query_update;
        query_update.prepare("select nome_produto,descricao_produto,username_usuario_cadastro_produto,"
                      "valor_produto,codigo_produto from cadastro_produtos order by nome_produto");
        if(query_update.exec()){
            while(query_update.next()){
                ui->tableWidget_cad_prod->insertRow(contlinhas);
                ui->tableWidget_cad_prod->setItem(contlinhas,0,new QTableWidgetItem(query_update.value(0).toString()));
                ui->tableWidget_cad_prod->setItem(contlinhas,1,new QTableWidgetItem(query_update.value(1).toString()));
                ui->tableWidget_cad_prod->setItem(contlinhas,2,new QTableWidgetItem(query_update.value(2).toString()));
                ui->tableWidget_cad_prod->setItem(contlinhas,3,new QTableWidgetItem(query_update.value(3).toString()));
                ui->tableWidget_cad_prod->setItem(contlinhas,4,new QTableWidgetItem(query_update.value(4).toString()));
                ui->tableWidget_cad_prod->setRowHeight(contlinhas,5);
                contlinhas++;
            }
        }else{
            QMessageBox::warning(this,"Erro","Erro ao listar produtos!");
        }
    }
}















