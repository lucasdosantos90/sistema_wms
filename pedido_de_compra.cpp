#include "pedido_de_compra.h"
#include "ui_pedido_de_compra.h"
#include "variaveis_globais.h"
#include <QMessageBox>
#include <QSqlQuery>

pedido_de_compra::pedido_de_compra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pedido_de_compra)
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
    QStringList cabecalho={"Código Produto",
"Nome produto","Quantidade","Preço","Preço Total","Localização"};
    ui->tableWidget->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QDate data=QDate::currentDate();
    ui->dateEdit_pedido_data_emissao->setDate(data);
    ui->dateEdit_pedido_prev_entrega->setDate(data);
}

pedido_de_compra::~pedido_de_compra()
{
    delete ui;
}

void pedido_de_compra::on_txt_cod_cli_returnPressed()
{
    int cod_cli=ui->txt_cod_cli->text().toInt();
    QSqlQuery query;
    query.prepare("select * from cadastro_clientes where id_cadastro_cliente "
" = "+QString::number(cod_cli)+" order by id_cadastro_cliente");
    if(!query.exec()){
        QMessageBox::warning(this,"Erro","Não foi possível exibir sua consulta!");
    }else{
        query.first();
        if(query.value(8).toInt()==cod_cli){
            ui->txt_nome_cli->setText(query.value(0).toString());
            ui->txt_cnpj_cli->setText(query.value(1).toString());
        }
    }
}

void pedido_de_compra::on_rb_cod_cli_clicked()
{
    if(!ui->txt_cod_cli->isEnabled()){
        ui->txt_cod_cli->setEnabled(true);
    }
    ui->rb_cod_cli->setEnabled(true);
    ui->rb_cod_cli->setDisabled(false);
    ui->txt_nome_cli->setDisabled(true);
    ui->txt_cnpj_cli->setDisabled(true);
    ui->txt_cod_cli->setFocus();
}

void pedido_de_compra::on_rb_nome_cli_clicked()
{
    if(!ui->txt_nome_cli->isEnabled()){
        ui->txt_nome_cli->setEnabled(true);
    }
        ui->rb_nome_cli->setEnabled(true);
        ui->rb_nome_cli->setDisabled(false);
        ui->txt_cod_cli->setDisabled(true);
        ui->txt_cnpj_cli->setDisabled(true);
        ui->txt_nome_cli->setFocus();
}

void pedido_de_compra::on_rb_cnpj_clicked()
{
    if(!ui->txt_cnpj_cli->isEnabled()){
        ui->txt_cnpj_cli->setEnabled(true);
    }
        ui->rb_cnpj->setEnabled(true);
        ui->rb_cnpj->setDisabled(false);
        ui->txt_cod_cli->setDisabled(true);
        ui->txt_nome_cli->setDisabled(true);
        ui->txt_cnpj_cli->setFocus();
}

void pedido_de_compra::on_rb_entrega_retirar_clicked()
{
        ui->txt_cod_transp->setEnabled(false);
        ui->txt_valor_frete->setEnabled(false);
}

void pedido_de_compra::on_rb_entrega_frete_clicked()
{
    if(!ui->txt_cod_transp->isEnabled()){
        ui->txt_cod_transp->setEnabled(true);
        ui->txt_valor_frete->setEnabled(true);
        ui->txt_cod_transp->setFocus();
    }else{
        ui->txt_cod_transp->setFocus();
    }
}

void pedido_de_compra::on_txt_cod_transp_returnPressed()
{
    int cod_transp=ui->txt_cod_transp->text().toInt();
    QSqlQuery query;
    query.prepare("select * from cadastro_transportadoras where id_cadastro_transportadora "
" = "+QString::number(cod_transp)+" order by id_cadastro_transportadora");
    if(!query.exec()){
        QMessageBox::warning(this,"Erro","Não foi possível exibir sua consulta!");
    }else{
        query.first();
        if(query.value(8).toInt()==cod_transp){
            ui->txt_valor_frete->setText(query.value(14).toString());
        }
    }
}

void pedido_de_compra::on_txt_prod_cod_returnPressed()
{
    if(ui->txt_prod_cod->text()==""){
        QMessageBox::warning(this,"Inválido","Digite um código para o item");
        ui->txt_prod_cod->setFocus();
    }else{
        int cod_prod=ui->txt_prod_cod->text().toInt();
        int qtde=0;
        QSqlQuery query;
        query.prepare("select * from produtos_no_estoque where codigo_produto"
        " = "+QString::number(cod_prod)+" order by codigo_produto");
        if(!query.exec()){
            QMessageBox::warning(this,"Erro","Não foi possível exibir sua consulta!");
        }else{
            while(query.next()){
                qtde+=query.value(2).toInt();
            }
            query.first();
            if(query.value(1).toInt()==cod_prod){
                ui->txt_prod_estoq_disp->setText(QString::number(qtde));
                ui->txt_prod_preco->setText(query.value(3).toString());
                ui->txt_nome_produto->setText(query.value(6).toString());
                ui->txt_prod_qtde->setFocus();
            }
        }
    }
}

void pedido_de_compra::on_txt_valor_desconto_returnPressed()
{
    if(ui->rb_tipo_desc_moeda->isChecked()){
        double total=(ui->txt_prod_preco->text().toDouble()-ui->txt_valor_desconto->text().toDouble());
        ui->txt_prod_preco->setText(QString::number(total));
    }else if(ui->rb_tipo_desc_porcent->isChecked()){
        double total=ui->txt_prod_preco->text().toDouble()-(ui->txt_prod_preco->text().toDouble()*((ui->txt_valor_desconto->text().toDouble())/100));
        ui->txt_prod_preco->setText(QString::number(total));
    }else if(!ui->rb_tipo_desc_moeda->isChecked() && !ui->rb_tipo_desc_porcent->isChecked()){
        QMessageBox::warning(this,"Atenção!","Escolha um dos tipos de desconto!\nPor valor, ou porcentagem!");
    }
}

void pedido_de_compra::on_rb_tipo_desc_moeda_clicked()
{
    ui->txt_valor_desconto->setFocus();
}

void pedido_de_compra::on_rb_tipo_desc_porcent_clicked()
{
    ui->txt_valor_desconto->setFocus();
}

void pedido_de_compra::on_btn_item_add_clicked()
{
    if(ui->txt_prod_qtde->text()==""){
        QMessageBox::warning(this,"Sem quantidade!","Digite alguma quantidade");
        ui->txt_prod_qtde->setFocus();
    }else{
        int cont=0;
        int contlinhas=0;
        QSqlQuery query;
        query.prepare("select * from produtos_no_estoque where codigo_produto"
        " = '"+ui->txt_prod_cod->text()+"' order by codigo_produto");
        if(query.exec()){
        if(ui->tableWidget->rowCount()>0){
            while(cont<ui->tableWidget->rowCount()){
                if(ui->tableWidget->item(cont,0)->text()==ui->txt_prod_cod->text()){
                    QMessageBox::StandardButton opc=QMessageBox::warning(this,"Atenção","Deseja adicionar o item\n"
                    +ui->txt_prod_cod->text()+" na lista novamente?",QMessageBox::Yes|QMessageBox::No);
                    if(opc==QMessageBox::Yes){
                        int item_lista=ui->tableWidget->item(cont,2)->text().toInt();
                        int item_formu=ui->txt_prod_qtde->text().toInt();
                        int soma=item_lista+item_formu;
                        ui->tableWidget->setItem(cont,2,new QTableWidgetItem(QString::number(soma)));
                        goto fim;
                        break;
                    }else if(opc==QMessageBox::No){
                        ui->txt_prod_cod->setText("");
                        ui->txt_prod_qtde->setText("");
                        ui->txt_prod_estoq_disp->setText("");
                        ui->txt_prod_preco->setText("");
                        ui->txt_prod_qtde->setText("");
                        ui->txt_prod_cod->setFocus();
                        goto fim;
                        break;
                    }
                }else{
                    cont++;
                }
            }
        }
           // while(query.next()){//ESSE WHILE TRAVAVA O PROGRAMA!
                query.first();
                ui->tableWidget->insertRow(contlinhas);
                ui->tableWidget->setItem(contlinhas,0,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget->setItem(contlinhas,1,new QTableWidgetItem(query.value(6).toString()));
                ui->tableWidget->setItem(contlinhas,2,new QTableWidgetItem(ui->txt_prod_qtde->text()));
                ui->tableWidget->setItem(contlinhas,3,new QTableWidgetItem(ui->txt_prod_preco->text()));
                double preco_total=(ui->txt_prod_qtde->text().toDouble()*ui->txt_prod_preco->text().toDouble());
                ui->tableWidget->setItem(contlinhas,4,new QTableWidgetItem(QString::number(preco_total)));
                ui->tableWidget->setItem(contlinhas,5,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget->setRowHeight(contlinhas,5);
            //}
    //        double pr_tot=(ui->txt_prod_qtde->text().toDouble()*ui->txt_prod_preco->text().toDouble());
    //        double val_total_ped=ui->txt_valor_total_ped->text().toDouble()+pr_tot;

    //        int qtde_item=ui->txt_prod_qtde->text().toInt();
    //        int qtde_total_item=ui->txt_quant_total_itens->text().toInt()+qtde_item;

    //        ui->txt_quant_total_itens->setText(QString::number(qtde_total_item));
    //        ui->txt_valor_total_ped->setText(QString::number(val_total_ped));
        }else{
            QMessageBox::warning(this,"Erro","Erro ao listar produtos!");
        }
        fim:;
        ui->txt_prod_cod->setText("");
        ui->txt_prod_qtde->setText("");
        ui->txt_prod_estoq_disp->setText("");
        ui->txt_prod_preco->setText("");
        ui->txt_prod_qtde->setText("");
        ui->txt_prod_cod->setFocus();
    }
}

void pedido_de_compra::on_btn_finalizar_ped_clicked()
{
    if(ui->tableWidget->rowCount()>0){
        QSqlQuery query;
        int total=ui->tableWidget->rowCount();
        int linha=0;
        while(linha<total){
            QString user_criou_ped=variaveis_globais::username;
            QString cod_ped=ui->txt_cod_ped->text();
            QString cod_cli=ui->txt_cod_cli->text();
            QString nome_cli=ui->txt_nome_cli->text();
            QString cnpj_cli=ui->txt_cnpj_cli->text();
            QString transp_cod=ui->txt_cod_transp->text();
            QString transp_val=ui->txt_valor_frete->text();
            QString item_cod=ui->tableWidget->item(linha,0)->text();
            QString item_nom=ui->tableWidget->item(linha,1)->text();
            QString item_qtd=ui->tableWidget->item(linha,2)->text();
            QString item_prc=ui->tableWidget->item(linha,3)->text();
            QString item_prc_total=ui->tableWidget->item(linha,4)->text();
            QString item_loc=ui->tableWidget->item(linha,5)->text();
            QString data_emiss=ui->dateEdit_pedido_data_emissao->text();
            QString data_prevs=ui->dateEdit_pedido_prev_entrega->text();
            QString qtde_total=ui->txt_quant_total_itens->text();
            query.prepare("insert into pedido_de_compra (codigo_pedido,codigo_cliente,"
        "nome_cliente,cnpj_cliente,codigo_transp,valor_frete,item_codigo,item_nome,"
        "item_quant,item_preco,item_preco_total,item_localizacao,data_emissao,"
        "previsao_entrega,qtde_total,usuario_criou_pedido)"
        "values ('"+cod_ped+"','"+cod_cli+"','"+nome_cli+"','"+cnpj_cli+"','"+transp_cod+"','"+transp_val+"',"
" '"+item_cod+"','"+item_nom+"',"+item_qtd+","+item_prc+","+item_prc_total+",'"+item_loc+"',"
"'"+data_emiss+"','"+data_prevs+"','"+qtde_total+"','"+user_criou_ped+"') ");
            query.exec();
            linha++;
        }
            QMessageBox::information(this,"Concluido!","Pedido concluído com sucesso!");            
            ui->txt_cod_ped->text().clear();
            ui->txt_cod_cli->text().clear();
            ui->txt_nome_cli->text().clear();
            ui->txt_cnpj_cli->text().clear();
            ui->txt_cod_transp->text().clear();
            ui->txt_valor_frete->text().clear();
            ui->txt_prod_cod->text().clear();
            ui->txt_prod_estoq_disp->text().clear();
            ui->txt_prod_preco->text().clear();
            ui->txt_prod_qtde->text().clear();
            ui->txt_valor_desconto->text().clear();
            ui->txt_nome_produto->text().clear();
            ui->txt_quant_total_itens->text().clear();
            while(ui->tableWidget->rowCount()>0){
                ui->tableWidget->removeRow(0);
            }
    }else{
        QMessageBox::warning(this,"Erro!","Não foi possível criar esse pedido!");
    }

}

void pedido_de_compra::on_btn_item_excluir_clicked()
{
    if(ui->tableWidget->currentColumn()!=-1){
        int r=ui->tableWidget->currentRow();
        int valor=ui->tableWidget->item(r,0)->text().toInt();
        QMessageBox::StandardButton opc=QMessageBox::question(this,"Deseja excluir?","Confirma excluir o item selecionado?\nitem:"+QString::number(valor),
QMessageBox::Yes|QMessageBox::No);
        if(opc==QMessageBox::Yes){
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
    }else{
        QMessageBox::warning(this,"Erro","Selecione um item primeiro!");
    }
}

void pedido_de_compra::on_btn_item_edit_clicked()
{
    if(ui->tableWidget->currentColumn()==-1){
        QMessageBox::warning(this,"Atenção!","Selecione um item para editar primeiro!");
    }else{
        int r=ui->tableWidget->currentRow();
        int valor=ui->tableWidget->item(r,0)->text().toInt();
        QMessageBox::StandardButton opc=QMessageBox::question(this,"Deseja editar?","O produto "+QString::number(valor)+" será excluído da lista para ser editado",
QMessageBox::Yes|QMessageBox::No);
        if(opc==QMessageBox::Yes){
            int cod_prod=valor;
            int qtde=0;
            QSqlQuery query;
            query.prepare("select * from produtos_no_estoque where codigo_produto"
        " = "+QString::number(valor)+" order by codigo_produto");
            if(!query.exec()){
                QMessageBox::warning(this,"Erro","Não foi possível exibir sua consulta!");
            }else{
                while(query.next()){
                    qtde+=query.value(2).toInt();
                }
                query.first();
                if(query.value(1).toInt()==cod_prod){
                    ui->txt_prod_cod->setText(QString::number(cod_prod));
                    ui->txt_prod_estoq_disp->setText(QString::number(qtde));
                    ui->txt_prod_preco->setText(query.value(3).toString());
                    ui->txt_nome_produto->setText(query.value(6).toString());
                    ui->txt_prod_qtde->setFocus();
                }
            }
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        }
    }
}

void pedido_de_compra::on_btn_novo_ped_clicked()
{
    QTime tempoAtual=QTime::currentTime();
    QDate dataAtual=QDate::currentDate();
    QString dataTexto=dataAtual.toString("MMyy");
    std::replace(dataTexto.begin(),dataTexto.end(),'/','0');
    dataTexto.toInt();
    QString tempoTexto=tempoAtual.toString("hhmmss");
    std::replace(tempoTexto.begin(),tempoTexto.end(),':','0');
    tempoTexto.toInt();
    ui->txt_cod_ped->setText(dataTexto+tempoTexto);
}

void pedido_de_compra::on_txt_prod_qtde_returnPressed()
{
    ui->btn_item_add->setFocus();
}


void pedido_de_compra::on_tableWidget_cellChanged(int row, int column)
{
    //TOTAL DE LINHAS
    int cont=0;
    if(ui->tableWidget->rowCount()>0){
        cont=ui->tableWidget->rowCount();
    }
    ui->txt_quant_total_itens->setText(QString::number(cont));

}
