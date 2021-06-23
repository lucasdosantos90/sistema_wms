#include "entrada_produtos_estoque.h"
#include "ui_entrada_produtos_estoque.h"
#include "janela_principal.h"
#include <QMessageBox>

entrada_produtos_estoque::entrada_produtos_estoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::entrada_produtos_estoque)
{
    ui->setupUi(this);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,100);
    QStringList cabecalho={"Código Produto","Nome Produto",
                           "Desc. Produto","Quantidade",
                           "Estoque","Localização"};
    ui->tableWidget->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->txt_estoq_origem->setText("EXP_02");
    ui->txt_loc_origem->setText("A-02");

}

entrada_produtos_estoque::~entrada_produtos_estoque()
{
    delete ui;
}

void entrada_produtos_estoque::on_txt_estoq_origem_returnPressed()
{

    QSqlQuery query;
    QString estoq_origem=ui->txt_estoq_origem->text();
    query.prepare("select setor_estoque from tabela_cadastro_estoque where setor_estoque "
                  " = '"+estoq_origem+"' order by setor_estoque ");
    query.exec();
    query.first();
    if(query.value(0).toString()==""){
        QMessageBox::warning(this,"Erro!","O Estoque '"+estoq_origem+"' \n não foi encontrado! ");
    }else{
        estoq_origem.clear();
        ui->txt_estoq_destino->setFocus();
        ui->txt_estoq_origem->setDisabled(true);
    }
}

void entrada_produtos_estoque::on_txt_estoq_destino_returnPressed()
{

    QSqlQuery query;
    QString estoq_destino=ui->txt_estoq_destino->text();
    query.prepare("select setor_estoque from tabela_cadastro_estoque where setor_estoque "
                  " = '"+estoq_destino+"' order by setor_estoque ");
    query.exec();
    query.first();
    if(query.value(0).toString()==""){
        QMessageBox::warning(this,"Erro!","O Estoque '"+estoq_destino+"' \n não foi encontrado! ");
    }else{
        estoq_destino.clear();
        ui->txt_loc_origem->setFocus();
        ui->txt_estoq_destino->setDisabled(true);
    }
}

void entrada_produtos_estoque::on_txt_loc_origem_returnPressed()
{

    QSqlQuery query;
    QString estoq_origem=ui->txt_loc_origem->text();
    query.prepare("select nome_localizacao from tabela_cadastro_estoque where nome_localizacao "
                  " = '"+estoq_origem+"' order by setor_estoque ");
    query.exec();
    query.first();
    if(query.value(0).toString()==""){
        QMessageBox::warning(this,"Erro!","A Localização '"+estoq_origem+"' \n não foi encontrado! ");
    }else{
        estoq_origem.clear();
        ui->txt_loc_destino->setFocus();
        ui->txt_loc_origem->setDisabled(true);
    }
}

void entrada_produtos_estoque::on_txt_loc_destino_returnPressed()
{

    QSqlQuery query;
    QString estoq_destino=ui->txt_loc_destino->text();
    query.prepare("select nome_localizacao from tabela_cadastro_estoque where nome_localizacao "
                  " = '"+estoq_destino+"' order by setor_estoque ");
    query.exec();
    query.first();
    if(query.value(0).toString()==""){
        QMessageBox::warning(this,"Erro!","A Localização '"+estoq_destino+"' \n não foi encontrado! ");
    }else{
        estoq_destino.clear();
        ui->txt_cod_produto->setFocus();
        ui->txt_loc_destino->setDisabled(true);
    }
}

void entrada_produtos_estoque::on_txt_cod_produto_returnPressed()
{
    if(ui->txt_cod_produto->text()==""){
        QMessageBox::warning(this,"Erro","Digite um produto!");
        ui->txt_cod_produto->setFocus();
        ui->txt_cod_produto->selectAll();
    }else{
        QString cod=ui->txt_cod_produto->text();
        QSqlQuery query;
        query.prepare("select codigo_produto from produtos no estoque where codigo_produto ="+cod+" order by codigo_produto ");
        query.exec();
        query.first();
        if(query.value(0).toString()==""){
            ui->txt_qtde_produto->setFocus();
        }else{
            QMessageBox::information(this,"Erro!","Produto "+cod+" não foi encontrado!");
        }
    }
}

void entrada_produtos_estoque::on_txt_qtde_produto_returnPressed()
{
    if(ui->txt_qtde_produto->text()==""){
        QMessageBox::warning(this,"Erro","Digite uma quantidade!");
        ui->txt_qtde_produto->setFocus();
        ui->txt_qtde_produto->selectAll();
    }else{
        QString cod=ui->txt_cod_produto->text();
        QString estoqorigem=ui->txt_estoq_origem->text();
        QString locorigem=ui->txt_loc_origem->text();
        int contlinhas=0;
        int cont=0;
        QSqlQuery query;
        query.prepare("select codigo_produto,nome_produto,descricao_produto,quantidade_produto,"
        " id_localizacao,codigo_estoque from produtos_no_estoque where codigo_produto = '"+cod+"'"
        " and codigo_estoque = '"+locorigem+"' ");
        query.exec();
        if(query.exec()){
            if(ui->tableWidget->rowCount()>0){
                while(cont<ui->tableWidget->rowCount()){
                    if(ui->tableWidget->item(cont,0)->text()==ui->txt_cod_produto->text()){
                        QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja adicionar o item \n"
                        +ui->txt_cod_produto->text()+" na lista?",QMessageBox::Yes|QMessageBox::No);
                        if(opc==QMessageBox::Yes){
                            //QMessageBox::information(this,"Duplicado!","já existe esse produto na lista!");
                            int s1=ui->tableWidget->item(cont,3)->text().toInt();
                            int s2=ui->txt_qtde_produto->text().toInt();
                            int soma=s1+s2;
                            ui->tableWidget->setItem(cont,3,new QTableWidgetItem(QString::number(soma)));
                            ui->txt_cod_produto->setText("");
                            ui->txt_qtde_produto->setText("");
                            ui->txt_cod_produto->setFocus();
                            goto fim;
                            break;
                        }else if(opc==QMessageBox::No){
                            ui->txt_qtde_produto->setFocus();
                            ui->txt_qtde_produto->selectAll();
                            goto fim;
                            break;
                        }
                    }else{
                        cont++;
                    }
                }
            }
            query.first();
            if(query.value(0).toString()==cod){
                    ui->tableWidget->insertRow(contlinhas);
                    ui->tableWidget->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                    ui->tableWidget->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                    ui->tableWidget->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                    ui->tableWidget->setItem(contlinhas,3,new QTableWidgetItem(ui->txt_qtde_produto->text()));
                    ui->tableWidget->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                    ui->tableWidget->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
                    ui->tableWidget->setRowHeight(contlinhas,6);
                    contlinhas++;
            }else{
                QMessageBox::information(this,"Erro","Não foi encontrado o produto: \n "+cod+" \n na localização: "+locorigem+" ");
                ui->txt_cod_produto->setFocus();
                ui->txt_cod_produto->selectAll();
            }
        }
        fim:;
    }
}

void entrada_produtos_estoque::on_btn_add_produtos_clicked()
{
    if(ui->txt_qtde_produto->text()==""){
        QMessageBox::warning(this,"Erro","Digite uma quantidade!");
        ui->txt_qtde_produto->setFocus();
        ui->txt_qtde_produto->selectAll();
    }else{
        QString cod=ui->txt_cod_produto->text();
        QString estoqorigem=ui->txt_estoq_origem->text();
        QString locorigem=ui->txt_loc_origem->text();
        int contlinhas=0;
        int cont=0;
        QSqlQuery query;
        query.prepare("select codigo_produto,nome_produto,descricao_produto,quantidade_produto,"
        " id_localizacao,codigo_estoque from produtos_no_estoque where codigo_produto = '"+cod+"'"
        " and codigo_estoque = '"+locorigem+"' ");
        query.exec();
        if(query.exec()){
            if(ui->tableWidget->rowCount()>0){
                while(cont<ui->tableWidget->rowCount()){
                    if(ui->tableWidget->item(cont,0)->text()==ui->txt_cod_produto->text()){
                        QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja adicionar o item \n"
                        +ui->txt_cod_produto->text()+" na lista?",QMessageBox::Yes|QMessageBox::No);
                        if(opc==QMessageBox::Yes){
                            //QMessageBox::information(this,"Duplicado!","já existe esse produto na lista!");
                            int s1=ui->tableWidget->item(cont,3)->text().toInt();
                            int s2=ui->txt_qtde_produto->text().toInt();
                            int soma=s1+s2;
                            ui->tableWidget->setItem(cont,3,new QTableWidgetItem(QString::number(soma)));
                            ui->txt_cod_produto->setText("");
                            ui->txt_qtde_produto->setText("");
                            ui->txt_cod_produto->setFocus();
                            goto fim;
                            break;
                        }else if(opc==QMessageBox::No){
                            ui->txt_qtde_produto->setFocus();
                            ui->txt_qtde_produto->selectAll();
                            goto fim;
                            break;
                        }
                    }else{
                        cont++;
                    }
                }
            }
            query.first();
            if(query.value(0).toString()==cod){
                    ui->tableWidget->insertRow(contlinhas);
                    ui->tableWidget->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                    ui->tableWidget->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                    ui->tableWidget->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                    ui->tableWidget->setItem(contlinhas,3,new QTableWidgetItem(ui->txt_qtde_produto->text()));
                    ui->tableWidget->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                    ui->tableWidget->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
                    ui->tableWidget->setRowHeight(contlinhas,6);
                    contlinhas++;
            }else{
                QMessageBox::information(this,"Erro","Não foi encontrado o produto: \n "+cod+" \n na localização: "+locorigem+" ");
                ui->txt_cod_produto->setFocus();
                ui->txt_cod_produto->selectAll();
            }
        }
        fim:;
    }
}

void entrada_produtos_estoque::on_btn_nova_transferencia_clicked()
{
    ui->txt_estoq_origem->setEnabled(true);
    ui->txt_estoq_origem->clear();
    ui->txt_estoq_destino->setEnabled(true);
    ui->txt_estoq_destino->clear();
    ui->txt_loc_origem->setEnabled(true);
    ui->txt_loc_origem->clear();
    ui->txt_loc_destino->setEnabled(true);
    ui->txt_loc_destino->clear();
    ui->txt_cod_produto->clear();
    ui->txt_qtde_produto->clear();
    while(ui->tableWidget->rowCount()>0){
        ui->tableWidget->removeRow(0);
    }
    ui->txt_estoq_origem->setFocus();
    ui->txt_estoq_origem->selectAll();
}

void entrada_produtos_estoque::on_btn_transferir_clicked()
{
    if(ui->tableWidget->rowCount()>0){
        QSqlQuery query;
        QSqlQuery query_pesq;
        int total=ui->tableWidget->rowCount();
        int linha=0;

        QString est_origem=ui->txt_estoq_origem->text();
        QString est_destino=ui->txt_estoq_destino->text();
        QString loc_origem=ui->txt_loc_origem->text();
        QString loc_destino=ui->txt_loc_destino->text();

        while(linha<total){
            QString cod_prod=ui->tableWidget->item(linha,0)->text();
            QString nome=ui->tableWidget->item(linha,1)->text();
            QString desc=ui->tableWidget->item(linha,2)->text();
            QString qtde=ui->tableWidget->item(linha,3)->text();
            QString est=ui->tableWidget->item(linha,4)->text();
            QString loc=ui->tableWidget->item(linha,5)->text();
            query.prepare("update produtos_no_estoque set codigo_estoque ='"+loc_destino+"', "
" codigo_produto = '"+cod_prod+"', quantidade_produto = '"+qtde+"', descricao_produto = '"+desc+"', "
" id_localizacao = '"+est_destino+"', nome_produto = '"+nome+"' "
" where codigo_produto = '"+cod_prod+"' and codigo_estoque = '"+loc_origem+"' ");
            query.exec();
            linha++;
            QMessageBox::information(this,"Transferido!","O item: "+cod_prod+" \n"
            "foi transferido da localização\n"+loc_origem+" "
            "para - "+loc_destino+" \n com sucesso! ");
        }
    }else{
        QMessageBox::warning(this,"Erro","Não há itens para serem transferidos!");
    }
}

















