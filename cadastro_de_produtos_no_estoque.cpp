#include "cadastro_de_produtos_no_estoque.h"
#include "ui_cadastro_de_produtos_no_estoque.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_de_produtos_no_estoque::cadastro_de_produtos_no_estoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_de_produtos_no_estoque)
{
    ui->setupUi(this);

    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget_estoq_disp->setColumnCount(4);
    ui->tableWidget_estoq_disp->setColumnWidth(0,50);
    ui->tableWidget_estoq_disp->setColumnWidth(1,100);
    QStringList cab_est_disp={"Nome Estoque(Setor)","Setor Estoque","Qtde. Máx","Nome Localização"};
    ui->tableWidget_estoq_disp->setHorizontalHeaderLabels(cab_est_disp);
    ui->tableWidget_estoq_disp->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_estoq_disp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_estoq_disp->verticalHeader()->setVisible(false);
    ui->tableWidget_estoq_disp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_estoq_disp->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_estoq_disp->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_add_prod->setColumnCount(5);
    ui->tableWidget_add_prod->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList cab_add_prod={"Código","Nome","Descrição","Quantidade","Valor"};
    ui->tableWidget_add_prod->setHorizontalHeaderLabels(cab_add_prod);
    ui->tableWidget_add_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_add_prod->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_estoq_disp->setEditTriggers(QAbstractItemView::SelectedClicked);
    ui->tableWidget_add_prod->verticalHeader()->setVisible(false);

    ui->txt_add_prod->setFocus();

    ui->tableWidget_add_prod->setItem(0,0,new QTableWidgetItem(""));

    while(ui->tableWidget_estoq_disp->rowCount()>0){
        ui->tableWidget_estoq_disp->removeRow(0);
    }
        int contlinhas=0;
        QSqlQuery query;
        query.prepare("select nome_localizacao,nome_estoque,quant_max_localizacao,"
        "setor_estoque from tabela_cadastro_estoque order by nome_localizacao");
        if(query.exec()){
            while(query.next()){
                ui->tableWidget_estoq_disp->insertRow(contlinhas);
                ui->tableWidget_estoq_disp->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget_estoq_disp->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget_estoq_disp->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget_estoq_disp->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget_estoq_disp->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget_estoq_disp->setRowHeight(contlinhas,5);
                contlinhas++;
            }
        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar estoque!");
        }        
}

cadastro_de_produtos_no_estoque::~cadastro_de_produtos_no_estoque()
{
    delete ui;
}

void cadastro_de_produtos_no_estoque::on_txt_add_prod_returnPressed()
{
    QSqlQuery query_pesq_prod;
    QString loc=ui->tableWidget_estoq_disp->item(ui->tableWidget_estoq_disp->currentRow(),0)->text();
    QString pesq_prod=ui->txt_add_prod->text();
    query_pesq_prod.exec("select * from produtos_no_estoque where codigo_produto ='"+pesq_prod+"'"
                         " and codigo_estoque = '"+loc+"' ");
    query_pesq_prod.first();
    if(query_pesq_prod.value(1).toString()==pesq_prod){
        QMessageBox::warning(this,"Erro","O produto "+pesq_prod+"\njá foi cadastrado na localização!");
        ui->txt_add_prod->setText("");
        ui->txt_add_prod->setFocus();
    }else{
        ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::NoSelection);
        if(!ui->tableWidget_estoq_disp->currentItem()){
            QMessageBox::warning(this,"ERRO","Estoque não Selecionado!");
        }else{
            int contlinhas=0;
            QSqlQuery query;
            QString addprod=ui->txt_add_prod->text();
            double valtotal;
    //        query.prepare("select codigo_produto,nome_produto,descricao_produto,"
    //        " quantidade_produto from cadastro_produtos where codigo_produto ="+addprod);
            query.prepare("select * from cadastro_produtos where codigo_produto ="+addprod);
            if(query.exec()){
                query.first();
                if(query.value(0).toString()!=""){
                        ui->tableWidget_add_prod->insertRow(contlinhas);
                        ui->tableWidget_add_prod->setItem(contlinhas,0,new QTableWidgetItem(query.value(7).toString()));
                        ui->tableWidget_add_prod->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                        ui->tableWidget_add_prod->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                        ui->tableWidget_add_prod->setItem(contlinhas,3,new QTableWidgetItem(query.value(8).toString()));
                        ui->tableWidget_add_prod->setItem(contlinhas,4,new QTableWidgetItem(query.value(6).toString()));
                        ui->tableWidget_add_prod->setRowHeight(contlinhas,5);
                        contlinhas++;
                }else{
                    QMessageBox::warning(this,"ERRO","Produto não encontrado!");
                }
            }else{
                QMessageBox::warning(this,"ERRO","Erro ao inserir novo produto!");
            }
        }
        ui->txt_add_prod->setText("");
        ui->txt_add_prod->setFocus();
    }
}

void cadastro_de_produtos_no_estoque::on_pushButton_clicked()
{
        QString addprod=ui->txt_add_prod->text();
        QString cod=ui->tableWidget_add_prod->item(0,0)->text();
        if(ui->tableWidget_add_prod->verticalHeader()->VLine>0){
        if(cod==addprod){
                QMessageBox::warning(this,"Duplicado","Já existe o item - "+cod);
            }
        }
}

void cadastro_de_produtos_no_estoque::on_btn_cad_prod_estoque_clicked()
{
    QSqlQuery query;
    int total=ui->tableWidget_add_prod->rowCount();
    int tw_estoq_disp=ui->tableWidget_estoq_disp->currentItem()->row();//??? currentItem()->row() ??? OU ??? currentIndex() ???
    int linha=0;
    while(linha<total){
        QString cod_estoque=ui->tableWidget_estoq_disp->item(tw_estoq_disp,0)->text();
        QString cod_produto=ui->tableWidget_add_prod->item(linha,0)->text();
        QString nome_estoque=ui->tableWidget_estoq_disp->item(tw_estoq_disp,3)->text();
        QString desc_produto=ui->tableWidget_add_prod->item(linha,2)->text();
        QString nome_produto=ui->tableWidget_add_prod->item(linha,1)->text();
        int quant_produto=ui->tableWidget_add_prod->item(linha,3)->text().toInt();
        double valor_prod=ui->tableWidget_add_prod->item(linha,4)->text().toDouble();

        query.prepare("insert into produtos_no_estoque (codigo_estoque,codigo_produto,id_localizacao,"
        " descricao_produto,quantidade_produto,nome_produto,valor_produto) values ('"+cod_estoque+"',"
        " '"+cod_produto+"','"+nome_estoque+"','"+desc_produto+"',"+QString::number(quant_produto)+","
        " '"+nome_produto+"',"+QString::number(valor_prod)+")");
        query.exec();
        linha++;
    }
    QMessageBox::information(this,"Cadastrado!","Itens Adicionado no estoque!");
}

void cadastro_de_produtos_no_estoque::on_tableWidget_estoq_disp_itemClicked(QTableWidgetItem *item)
{
    ui->tableWidget_estoq_disp->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_estoq_disp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_estoq_disp->setEditTriggers(QAbstractItemView::SelectedClicked);
    ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::SingleSelection);
    while(ui->tableWidget_add_prod->rowCount()>0){
        ui->tableWidget_add_prod->removeRow(0);
    }
//    auto mouse=ui->tableWidget_estoq_disp->item(ui->tableWidget_estoq_disp->currentIndex().row(),3)->text();
//    auto index=ui->tableWidget_estoq_disp->verticalHeaderItem(ui->tableWidget_estoq_disp->currentIndex().row())->text();
//    ui->label_localizacao->setText(index);
//    if(ui->tableWidget_add_prod->rowCount()>0){
//        QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja trocar a localização?",QMessageBox::Yes|QMessageBox::No);;
//        if(opc==QMessageBox::Yes){
//            //ui->tableWidget_add_prod->clear();
//            ui->tableWidget_add_prod->setColumnCount(4);
//            ui->tableWidget_add_prod->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//            QStringList cab_add_prod={"Código","Nome","Descrição","Quantidade"};
//            ui->tableWidget_add_prod->setHorizontalHeaderLabels(cab_add_prod);
//            ui->tableWidget_add_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);
//            ui->tableWidget_estoq_disp->setEditTriggers(QAbstractItemView::SelectedClicked);
//            ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::SingleSelection);
//            ui->tableWidget_add_prod->verticalHeader()->setVisible(false);

//            ui->txt_add_prod->setFocus();

//            while(ui->tableWidget_add_prod->rowCount()>0){
//                ui->tableWidget_add_prod->removeRow(0);
//            }
//        }else{
//            ui->tableWidget_estoq_disp->item(ui->tableWidget_estoq_disp->currentIndex().row(),3)->text();
//            ui->tableWidget_add_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);
//            ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::NoSelection);
//            ui->tableWidget_estoq_disp->setSelectionMode(QAbstractItemView::SingleSelection);
//        }
//    }
}

void cadastro_de_produtos_no_estoque::on_tableWidget_estoq_disp_itemSelectionChanged()
{
//    if(ui->tableWidget_add_prod->rowCount()>0){
//        QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja trocar a localização?",QMessageBox::Yes|QMessageBox::No);;
//        if(opc==QMessageBox::Yes){

//            ui->txt_add_prod->setFocus();

//            while(ui->tableWidget_add_prod->rowCount()>0){
//                ui->tableWidget_add_prod->removeRow(0);
//            }
//        }else{
//            ui->tableWidget_estoq_disp->selectRow(ui->label_localizacao->text().toInt());
//        }
//    }
}

void cadastro_de_produtos_no_estoque::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        while(ui->tableWidget_consulta_estoque->rowCount()>0){
            ui->tableWidget_consulta_estoque->removeRow(0);
        }
        ui->tableWidget_consulta_estoque->setColumnCount(4);
        ui->tableWidget_consulta_estoque->setColumnWidth(0,50);
        ui->tableWidget_consulta_estoque->setColumnWidth(1,100);
        QStringList cab_nome={"Nome Estoque(Setor)","Setor Estoque","Qtde. Máx","Nome Localização"};
        ui->tableWidget_consulta_estoque->setHorizontalHeaderLabels(cab_nome);
        ui->tableWidget_consulta_estoque->setStyleSheet("QTableView {selection-background-color:blue}");
        ui->tableWidget_consulta_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_consulta_estoque->verticalHeader()->setVisible(false);
        ui->tableWidget_consulta_estoque->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_consulta_estoque->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget_consulta_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_consulta_estoque->setSelectionMode(QAbstractItemView::SingleSelection);

            int contlinhas=0;
            QSqlQuery query;
            query.prepare("select nome_localizacao,nome_estoque,quant_max_localizacao,"
            "setor_estoque from tabela_cadastro_estoque order by nome_localizacao");
            if(query.exec()){
                while(query.next()){
                    ui->tableWidget_consulta_estoque->insertRow(contlinhas);
                    ui->tableWidget_consulta_estoque->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                    ui->tableWidget_consulta_estoque->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                    ui->tableWidget_consulta_estoque->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                    ui->tableWidget_consulta_estoque->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
                    ui->tableWidget_consulta_estoque->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                    ui->tableWidget_consulta_estoque->setRowHeight(contlinhas,5);
                    contlinhas++;
                }
            }else{
                QMessageBox::warning(this,"ERRO","Erro ao listar estoque!");
            }

    }
}

void cadastro_de_produtos_no_estoque::on_tableWidget_consulta_estoque_itemClicked(QTableWidgetItem *item)
{
    while(ui->tableWidget_consulta_prod->rowCount()>0){
        ui->tableWidget_consulta_prod->removeRow(0);
        ui->txt_filtrar_estoque->setFocus();
    }
    QSqlQuery query;
    QString loc=ui->tableWidget_consulta_estoque->item(ui->tableWidget_consulta_estoque->currentRow(),0)->text();
    if(query.exec("select * from produtos_no_estoque where codigo_estoque='"+loc+"' order by codigo_estoque ")){
        query.first();
        if(query.value(0).toString()==""){
            QMessageBox::information(this,"Erro","Não há itens cadastrados neste estoque!");
        }else{
            ui->tableWidget_consulta_prod->setColumnCount(4);
            ui->tableWidget_consulta_prod->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            QStringList cab_add_prod={"Código","Nome","Descrição","Quantidade"};
            ui->tableWidget_consulta_prod->setHorizontalHeaderLabels(cab_add_prod);
            ui->tableWidget_consulta_prod->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget_consulta_prod->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tableWidget_consulta_prod->setEditTriggers(QAbstractItemView::SelectedClicked);
            ui->tableWidget_consulta_prod->verticalHeader()->setVisible(false);
            int contlinhas=0;
            QSqlQuery query_cons;
            query_cons.prepare("select codigo_produto,nome_produto,descricao_produto,quantidade_produto from produtos_no_estoque where"
" codigo_estoque='"+loc+"' order by codigo_produto ");
            if(query_cons.exec()){
                while(query_cons.next()){
                    ui->tableWidget_consulta_prod->insertRow(contlinhas);
                    ui->tableWidget_consulta_prod->setItem(contlinhas,0,new QTableWidgetItem(query_cons.value(0).toString()));
                    ui->tableWidget_consulta_prod->setItem(contlinhas,1,new QTableWidgetItem(query_cons.value(1).toString()));
                    ui->tableWidget_consulta_prod->setItem(contlinhas,2,new QTableWidgetItem(query_cons.value(2).toString()));
                    ui->tableWidget_consulta_prod->setItem(contlinhas,3,new QTableWidgetItem(query_cons.value(3).toString()));
                    ui->tableWidget_consulta_prod->setItem(contlinhas,4,new QTableWidgetItem(query_cons.value(4).toString()));
                    ui->tableWidget_consulta_prod->setRowHeight(contlinhas,5);
                    contlinhas++;
                }
            }
        }
    }


//    while(ui->tableWidget_consulta_prod->rowCount()>0){
//        ui->tableWidget_consulta_prod->removeRow(0);
//    }

//    ui->tableWidget_consulta_prod->setItem(0,0,new QTableWidgetItem);
}
