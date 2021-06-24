#include "separacao_de_pedidos.h"
#include "ui_separacao_de_pedidos.h"
#include "variaveis_globais.h"
#include <QSqlQuery>
#include <QMessageBox>

static int num_ped;


separacao_de_pedidos::separacao_de_pedidos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::separacao_de_pedidos)
{
    ui->setupUi(this);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }
    ui->tableWidget->setVisible(false);
    ui->tableWidget->setColumnCount(17);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,100);
    QStringList cabecalho={"Cod. Pedido","Cod. Cliente","Nome Cliente","CNPJ Cliente","Cod. Transp"
"Val. Frete","Item Código","Item Nome","Item Qtde","Item Preço","Item Preço Total","Item Localização"
"Data Emissão","Previsão de Entrega","Qtde total do Pedido","Usuário criou Pedido"};
    ui->tableWidget->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

separacao_de_pedidos::~separacao_de_pedidos()
{
    delete ui;
}

void separacao_de_pedidos::on_txt_ped_num_returnPressed()
{
    num_ped=0;
    while(ui->tableWidget->rowCount()>0){
        ui->tableWidget->removeRow(0);
    }
    QString cod_ped=ui->txt_ped_num->text();
    QSqlQuery query;
    int linhas=0;
    query.prepare("select * from pedido_de_compra where codigo_pedido "
" = '"+cod_ped+"'");
        if(query.exec()){
            while(query.next()){
                ui->tableWidget->insertRow(linhas);
                ui->tableWidget->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget->setItem(linhas,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget->setItem(linhas,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget->setItem(linhas,5,new QTableWidgetItem(query.value(5).toString()));
                ui->tableWidget->setItem(linhas,6,new QTableWidgetItem(query.value(6).toString()));
                ui->tableWidget->setItem(linhas,7,new QTableWidgetItem(query.value(7).toString()));
                ui->tableWidget->setItem(linhas,8,new QTableWidgetItem(query.value(8).toString()));
                ui->tableWidget->setItem(linhas,9,new QTableWidgetItem(query.value(9).toString()));
                ui->tableWidget->setItem(linhas,10,new QTableWidgetItem(query.value(10).toString()));
                ui->tableWidget->setItem(linhas,11,new QTableWidgetItem(query.value(11).toString()));
                ui->tableWidget->setItem(linhas,12,new QTableWidgetItem(query.value(12).toString()));
                ui->tableWidget->setItem(linhas,13,new QTableWidgetItem(query.value(13).toString()));
                ui->tableWidget->setItem(linhas,14,new QTableWidgetItem(query.value(14).toString()));
                ui->tableWidget->setItem(linhas,15,new QTableWidgetItem(query.value(15).toString()));
                ui->tableWidget->setItem(linhas,16,new QTableWidgetItem(query.value(16).toString()));
                ui->tableWidget->setItem(linhas,17,new QTableWidgetItem(query.value(17).toString()));
                ui->tableWidget->setRowHeight(linhas,18);
                linhas++;
            }
            ui->txt_ped_qtde_total->setText(QString::number(linhas));
            ui->txt_ped_qtde_rest->setText(QString::number(linhas));
        }
        query.first();
        ui->tableWidget->selectRow(num_ped);
        ui->txt_ped_loc->setText(query.value(12).toString());
        ui->txt_ped_nome_prod->setText(query.value(7).toString());
        ui->txt_ped_item_qtde_a_passar->setText(query.value(8).toString());
        ui->txt_ped_cod_produto->setFocus();
}

void separacao_de_pedidos::on_btn_proximo_clicked()
{
    int linha=ui->tableWidget->currentRow();    
    ui->tableWidget->selectRow(linha+1);
    ui->txt_ped_item_qtde_a_passar->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),8)->text());
    ui->txt_ped_cod_produto->clear();
    ui->txt_ped_item_qtde->clear();
    ui->txt_ped_cod_produto->setFocus();
}

void separacao_de_pedidos::on_btn_anterior_clicked()
{
    int linha=ui->tableWidget->currentRow();
    ui->tableWidget->selectRow(linha-1);
    ui->txt_ped_item_qtde_a_passar->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),8)->text());
    ui->txt_ped_cod_produto->clear();
    ui->txt_ped_item_qtde->clear();
    ui->txt_ped_cod_produto->setFocus();
}

void separacao_de_pedidos::on_tableWidget_itemSelectionChanged()
{
//    QString nome_item=ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
//    //ui->tableWidget->item(num_ped,0)->text().toInt();
//    QSqlQuery query;
//    query.prepare("select * from pedido_de_compra where item_nome ='"+nome_item+"' ");
//    if(query.exec()){
//        query.first();
        ui->txt_ped_loc->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),12)->text());
        ui->txt_ped_nome_prod->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),7)->text());
    //}
}

void separacao_de_pedidos::on_txt_ped_cod_produto_returnPressed()
{
    QString cod_prod=ui->txt_ped_cod_produto->text();
    QString nome_prod=ui->txt_ped_nome_prod->text();
    QString cod_ped=ui->txt_ped_num->text();
    QSqlQuery query_item_cod;
    query_item_cod.prepare("select * from pedido_de_compra where "
    " item_codigo ='"+cod_prod+"' and item_nome ='"+nome_prod+"' "
    " and codigo_pedido ='"+cod_ped+"' order by item_codigo ");
    query_item_cod.exec();
    query_item_cod.first();
    if(cod_prod==query_item_cod.value(6).toString()){
        ui->txt_ped_item_qtde->setFocus();
    }else{
        QMessageBox::warning(this,"Erro","Produto digitado é diferente!");
        ui->txt_ped_cod_produto->setFocus();
        ui->txt_ped_cod_produto->selectAll();
    }
}

void separacao_de_pedidos::on_txt_ped_item_qtde_returnPressed()
{
    int qtde_pedido=ui->txt_ped_item_qtde->text().toInt();
    int linha=ui->tableWidget->currentRow();
    QString cod_ped=ui->txt_ped_num->text();
    QString cod_est=ui->txt_ped_loc->text();
    QString cod_prod=ui->txt_ped_cod_produto->text();
    QString nome_prod=ui->txt_ped_nome_prod->text();
    QSqlQuery query_estoque,query_ped,query_pedido,query_quant_atual;
    query_estoque.prepare("select * from produtos_no_estoque where codigo_estoque = '"+cod_est+"'"
" and codigo_produto = '"+cod_prod+"' order by quantidade_produto ");
    query_estoque.exec();
    query_estoque.first();
    query_pedido.prepare("select * from pedido_de_compra where "
    " item_codigo ='"+cod_prod+"' and item_nome ='"+nome_prod+"' "
    " and codigo_pedido ='"+cod_ped+"' order by item_codigo ");
    query_pedido.exec();
    query_pedido.first();
    if(qtde_pedido<=query_estoque.value(2).toInt() && qtde_pedido<=query_pedido.value(8).toInt()){
        int result=0;
        result=query_pedido.value(9).toInt()+qtde_pedido;
        if(result>query_pedido.value(8).toInt()){
            QMessageBox::information(this,"Erro","Quantidade não permitida!");
            ui->txt_ped_item_qtde->setFocus();
            ui->txt_ped_item_qtde->selectAll();
        }else{
            query_ped.prepare("update pedido_de_compra set item_quant_separado"
    " ="+QString::number(result)+" where codigo_pedido ='"+cod_ped+"' and"
    " item_codigo ='"+cod_prod+"' and item_nome ='"+nome_prod+"'  ");
            query_ped.exec();
            QMessageBox::information(this,"Item passado!","Produto passado!");
                QSqlQuery query_consulta;
                query_consulta.prepare("select * from produtos_no_estoque where codigo_estoque = '"+cod_est+"' "
            " and codigo_produto = '"+cod_prod+"' order by quantidade_produto ");
                query_consulta.exec();
                query_consulta.first();
                int quant_atual=0;
                quant_atual=query_consulta.value(2).toInt()-result;
                query_quant_atual.prepare("update produtos_no_estoque set quantidade_produto ="+QString::number(quant_atual)+" "
        " where codigo_produto ='"+cod_prod+"' and nome_produto ='"+nome_prod+"' and codigo_estoque ='"+cod_est+"' ");
                query_quant_atual.exec();

            ui->txt_ped_item_qtde->clear();
            ui->txt_ped_cod_produto->clear();
            ui->txt_ped_cod_produto->setFocus();
            query_pedido.exec();
            query_pedido.first();
            if(query_pedido.value(8).toInt()==query_pedido.value(9).toInt()){
               ui->tableWidget->selectRow(linha+1);
               int qtde=ui->txt_ped_qtde_rest->text().toInt();
               ui->txt_ped_qtde_rest->setText(QString::number(qtde-1));
               if(ui->txt_ped_qtde_rest->text().toInt()<=0){
                   ui->txt_ped_qtde_rest->setText(QString::number(0));
                   QMessageBox::information(this,"Finalizado!","Produto finzalizado!");
                   ui->txt_ped_num->setText("");
                   ui->txt_ped_loc->setText("");
                   ui->txt_ped_nome_prod->setText("");
                   ui->txt_ped_caixa->setText("");
                   ui->txt_ped_caixa_itens->setText("");
                   ui->txt_ped_qtde_total->setText("");
                   ui->txt_ped_qtde_rest->setText("");
                   ui->txt_ped_linha_atual->setText("");
                   ui->txt_ped_cod_produto->setText("");
                   ui->txt_ped_item_qtde_a_passar->setText("");
                   ui->txt_ped_item_qtde->setText("");
               }
            }
        }
    }else{
        QMessageBox::warning(this,"Erro!","Quantidade errada!");
    }

}














