#include "cadastro_estoque.h"
#include "ui_cadastro_estoque.h"
#include "variaveis_globais.h"
#include "janela_principal.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_estoque::cadastro_estoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_estoque)
{
    ui->setupUi(this);
    //DEPOIS CRIAR ISSO COMO FUNCAO PARA DIMINUIR LINHAS
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
    con.abrir();

    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget_cad_estoque->setColumnCount(5);
//    ui->tableWidget_cad_estoque->setColumnWidth(0,30);
//    ui->tableWidget_cad_estoque->setColumnWidth(1,200);
//    ui->tableWidget_cad_estoque->setColumnWidth(2,100);
//    ui->tableWidget_cad_estoque->setColumnWidth(3,150);
//    ui->tableWidget_cad_estoque->setColumnWidth(4,200);
    QStringList cabecalho={"ID","Nome Estoque","Setor Estoque","Nome Localização", "Quantidade Máxima"};
    ui->tableWidget_cad_estoque->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget_cad_estoque->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_cad_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_cad_estoque->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_cad_estoque->verticalHeader()->setVisible(false);
    ui->tableWidget_cad_estoque->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_cad_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //DEPOIS CRIAR ISSO COMO FUNCAO PARA DIMINUIR LINHAS
    while(ui->tableWidget_cad_estoque->rowCount()>0){
        ui->tableWidget_cad_estoque->removeRow(0);
    }
        int contlinhas = 0;
        QSqlQuery query;
        query.prepare("select * from tabela_cadastro_estoque order by id_estoque");
        if(query.exec()){
            while(query.next()){
                ui->tableWidget_cad_estoque->insertRow(contlinhas);
                ui->tableWidget_cad_estoque->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget_cad_estoque->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget_cad_estoque->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget_cad_estoque->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget_cad_estoque->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget_cad_estoque->setRowHeight(contlinhas,5);
                contlinhas++;
            }
        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar estoque!");
        }
}

cadastro_estoque::~cadastro_estoque()
{
    delete ui;
}

void cadastro_estoque::on_tabWidget_currentChanged(int index)
{
//    if(index==0){
//        while(ui->tableWidget_cad_estoque->rowCount()>0){
//            ui->tableWidget_cad_estoque->removeRow(0);
//        }
//        banco_de_dados.open();
//        int contlinhas = 0;
//        QSqlQuery query;
//        query.prepare("select * from tabela_cadastro_estoque order by id_estoque");
//        if(query.exec()){
//            while(query.next()){
//                ui->tableWidget_cad_estoque->insertRow(contlinhas);
//                ui->tableWidget_cad_estoque->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
//                ui->tableWidget_cad_estoque->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
//                ui->tableWidget_cad_estoque->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
//                ui->tableWidget_cad_estoque->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
//                ui->tableWidget_cad_estoque->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
//                ui->tableWidget_cad_estoque->setRowHeight(contlinhas,5);
//                contlinhas++;
//            }
//        }else{
//            QMessageBox::warning(this,"ERRO","Erro ao listar estoque!");
//        }
//        banco_de_dados.close();
//    }

}

void cadastro_estoque::on_btn_cad_estoque_clicked()
{
    QString nome_estoque=ui->txt_cad_nome_estoque->text();
    QString setor_estoque=ui->txt_cad_setor_estoque->text();
    QString nome_localizacao=ui->txt_cad_nome_localizacao->text();
    QString quant_max_loc=ui->txt_cad_quant_max_loc->text();

    QSqlQuery query;
    query.prepare("insert into tabela_cadastro_estoque (nome_estoque,setor_estoque,"
                  "nome_localizacao,quant_max_localizacao) values('"+nome_estoque+"',"
                  "'"+setor_estoque+"','"+nome_localizacao+"','"+quant_max_loc+"')");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar estoque!");
    }else{
        QMessageBox::warning(this,"OK","Estoque cadastrado!");
    }
}

















