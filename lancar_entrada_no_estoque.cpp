#include "lancar_entrada_no_estoque.h"
#include "ui_lancar_entrada_no_estoque.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

lancar_entrada_no_estoque::lancar_entrada_no_estoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lancar_entrada_no_estoque)
{
    ui->setupUi(this);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->tableWidget_local_estoque->setColumnCount(5);
    ui->tableWidget_local_estoque->setColumnWidth(0,50);
    ui->tableWidget_local_estoque->setColumnWidth(1,100);
    QStringList cabe_local={"ID Estoque","nome estoque",
"setor estoque","nome localizacao","quant.max.localização"};
    ui->tableWidget_local_estoque->setHorizontalHeaderLabels(cabe_local);
    ui->tableWidget_local_estoque->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_local_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_local_estoque->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_local_estoque->verticalHeader()->setVisible(false);
    ui->tableWidget_local_estoque->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_local_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget_lancar_produtos->setColumnCount(4);
    ui->tableWidget_lancar_produtos->setColumnWidth(0,50);
    ui->tableWidget_lancar_produtos->setColumnWidth(1,100);
    QStringList cabe_lancar={"Nome produto","Descrição produto",
"Código produto","Quantidade"};
    ui->tableWidget_lancar_produtos->setHorizontalHeaderLabels(cabe_lancar);
    ui->tableWidget_lancar_produtos->setStyleSheet("QTableView {selection-background-color:green}");
    ui->tableWidget_lancar_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_lancar_produtos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_lancar_produtos->verticalHeader()->setVisible(false);
    ui->tableWidget_lancar_produtos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_lancar_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

lancar_entrada_no_estoque::~lancar_entrada_no_estoque()
{
    delete ui;
}
void lancar_entrada_no_estoque::on_txt_add_qtde_produto_returnPressed()
{
    if(!ui->tableWidget_local_estoque->currentItem()){
        QMessageBox::warning(this,"Erro","Nenhum estoque selecionado!");
    }else if(ui->txt_add_produto->text()==""){
        QMessageBox::warning(this,"Erro","Primeiro digite o código de um produto!");
        ui->txt_add_produto->setFocus();
    }else{

        int contlinhas=0;
        QString busca;
        QSqlQuery query;
        if(ui->txt_add_produto->text()!=""){
            busca="select nome_produto,descricao_produto,codigo_produto,"
            " quantidade_produto from cadastro_produtos"
            " where codigo_produto ="+ui->txt_add_produto->text()+" ";
        }
        query.prepare(busca);
        if(query.exec()){
            int cont=0;

            //-------------------------------------------------//-------------------------------------------------
            //-------------------------------------------------//-------------------------------------------------

            QSqlQuery query_pesq_prod;
            QString loc=ui->tableWidget_local_estoque->item(ui->tableWidget_local_estoque->currentRow(),3)->text();
            query_pesq_prod.exec("select * from produtos_no_estoque where codigo_estoque "
                                 "= '"+loc+"' and codigo_produto = '"+ui->txt_add_produto->text()+"' order by codigo_estoque");
            query_pesq_prod.first();
            if(query_pesq_prod.value(0).toString()==""){
                QMessageBox::information(this,"Erro","Produto não cadastrado!");
                goto fim;
            }

            //-------------------------------------------------//-------------------------------------------------
            //-------------------------------------------------//-------------------------------------------------


            if(ui->tableWidget_lancar_produtos->rowCount()>0){
                while(cont<ui->tableWidget_lancar_produtos->rowCount()){
                    if(ui->tableWidget_lancar_produtos->item(cont,2)->text()==ui->txt_add_produto->text()){
                        QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja adicionar o item \n"
                        +ui->txt_add_produto->text()+" na lista?",QMessageBox::Yes|QMessageBox::No);
                        if(opc==QMessageBox::Yes){
                            //QMessageBox::information(this,"Duplicado!","já existe esse produto na lista!");
                            int s1=ui->tableWidget_lancar_produtos->item(cont,3)->text().toInt();
                            int s2=ui->txt_add_qtde_produto->text().toInt();
                            int soma=s1+s2;
                            ui->tableWidget_lancar_produtos->setItem(cont,3,new QTableWidgetItem(QString::number(soma)));
                            goto fim;
                            break;
                        }else if(opc==QMessageBox::No){
                            ui->txt_add_produto->setText("");
                            ui->txt_add_qtde_produto->setText("");
                            ui->txt_add_produto->setFocus();
                            goto fim;
                            break;
                        }
                    }else{
                        cont++;
                    }
                }
            }
            while(query.next()){
                    ui->tableWidget_lancar_produtos->insertRow(contlinhas);
                    ui->tableWidget_lancar_produtos->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                    ui->tableWidget_lancar_produtos->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                    ui->tableWidget_lancar_produtos->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                    ui->tableWidget_lancar_produtos->setItem(contlinhas,3,new QTableWidgetItem(ui->txt_add_qtde_produto->text()));
                    ui->tableWidget_lancar_produtos->setRowHeight(contlinhas,4);
                    contlinhas++;
            }
        }
        fim:;
    }
//    fim:
    ui->txt_add_produto->setText("");
    ui->txt_add_qtde_produto->setText("");
    ui->txt_add_produto->setFocus();
}

void lancar_entrada_no_estoque::on_txt_local_estoque_returnPressed()
{

    while(ui->tableWidget_local_estoque->rowCount()>0){
        ui->tableWidget_local_estoque->removeRow(0);
    }
    int contlinhas=0;
    QString busca;
    if(ui->txt_local_estoque->text()!=""){
        busca="select * from tabela_cadastro_estoque where "
    " nome_localizacao like '%"+ui->txt_local_estoque->text()+"%' "
    " order by nome_localizacao";
    }
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec()){
        while(query.next()){
            ui->tableWidget_local_estoque->insertRow(contlinhas);
            ui->tableWidget_local_estoque->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_local_estoque->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_local_estoque->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget_local_estoque->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget_local_estoque->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget_local_estoque->setRowHeight(contlinhas,5);
            contlinhas++;
        }
    }
    ui->txt_local_estoque->setText("");
}

void lancar_entrada_no_estoque::on_txt_add_produto_returnPressed()
{
    if(ui->txt_add_produto->text()==""){
        QMessageBox::warning(this,"Atenção!","Informe um produto para lançar no estoque!");
        ui->txt_add_produto->setFocus();
    }else{
        ui->txt_add_qtde_produto->setFocus();
    }
}

void lancar_entrada_no_estoque::on_tableWidget_local_estoque_itemClicked(QTableWidgetItem *item)
{

    QSqlQuery query;
    QString loc=ui->tableWidget_local_estoque->item(ui->tableWidget_local_estoque->currentRow(),3)->text();
    if(query.exec("select * from produtos_no_estoque where codigo_estoque='"+loc+"' ")){
        query.first();
        if(query.value(0).toString()==""){
            QMessageBox::information(this,"Erro","Não há itens cadastrados neste estoque!");
            while(ui->tableWidget_local_estoque->rowCount()>0){
                ui->tableWidget_local_estoque->removeRow(0);
                ui->txt_local_estoque->setFocus();
            }
        }else{
            ui->txt_add_produto->setFocus();
        }
    }


    while(ui->tableWidget_lancar_produtos->rowCount()>0){
        ui->tableWidget_lancar_produtos->removeRow(0);
    }

    ui->tableWidget_lancar_produtos->setItem(0,0,new QTableWidgetItem);
}

void lancar_entrada_no_estoque::on_pushButton_clicked()
{

    QSqlQuery query_prodestoq;
    int cont=0;
    query_prodestoq.exec("select * from produtos_no_estoque order by codigo_produto");
    while(query_prodestoq.next()){
        if(query_prodestoq.value(1).isValid()){
            cont++;
        }
    }
    QMessageBox::information(this,"",""+QString::number(cont));
    //QMessageBox::warning(this,"Resultado","tem "+query_prodestoq.record());
//    int cont=0;
//    while(cont<ui->tableWidget_lancar_produtos->rowCount()){
//        if(ui->tableWidget_lancar_produtos->item(cont,2)->text()==ui->txt_add_produto->text()){
//            QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja adicionar o item \n"
//            +ui->txt_add_produto->text()+" na lista?",QMessageBox::Yes|QMessageBox::No);
//            if(opc==QMessageBox::Yes){
//                //QMessageBox::information(this,"Duplicado!","já existe esse produto na lista!");
//                int s1=ui->tableWidget_lancar_produtos->item(cont,3)->text().toInt();
//                int s2=ui->txt_add_qtde_produto->text().toInt();
//                int soma=s1+s2;
//                ui->tableWidget_lancar_produtos->setItem(cont,3,new QTableWidgetItem(QString::number(soma)));
//                break;
//            }else if(opc==QMessageBox::No){
//                ui->txt_add_produto->setText("");
//                ui->txt_add_qtde_produto->setText("");
//                ui->txt_add_produto->setFocus();
//                break;
//            }
//        }else{
//            cont++;
//        }
//    }
}

void lancar_entrada_no_estoque::on_btn_lancar_estoque_clicked()
{
    if(ui->tableWidget_lancar_produtos->rowCount()>0){

        QSqlQuery query;
        QSqlQuery query_pesq_prod;
        int total=ui->tableWidget_lancar_produtos->rowCount();
        int linha=0;        
        while(linha<total){
            QString quantidade=ui->tableWidget_lancar_produtos->item(linha,3)->text();
            QString loc=ui->tableWidget_local_estoque->item(ui->tableWidget_local_estoque->currentRow(),3)->text();
            QString codigo=ui->tableWidget_lancar_produtos->item(linha,2)->text();

            query_pesq_prod.exec("select * from produtos_no_estoque where codigo_estoque "
                                 "= '"+loc+"' and codigo_produto = '"+codigo+"' order by codigo_produto");
            query_pesq_prod.first();

            int result=0;
            result=query_pesq_prod.value(2).toInt()+quantidade.toInt();
            //QMessageBox::information(this,"","QTDE: "+QString::number(result)+"!+"+query_pesq_prod.value(2).toString());
//------------------FUNCIONA, E ADICIONA OK !!!!!!!------------------------------------------------------------------------
            query.prepare("update produtos_no_estoque set quantidade_produto ="+QString::number(result)+" "
                          " where codigo_estoque ='"+loc+"' and codigo_produto ='"+codigo+"' ");
//-------------------------------------------------------------------------------------------------------------------------
            query.exec();
            linha++;
        }
        QMessageBox::information(this,"Cadastrado!","Itens adicionados ao estoque!");
    }else{
        QMessageBox::warning(this,"Erro","Não há quantidade de itens para serem lançados no estoque!");
    }


}
























