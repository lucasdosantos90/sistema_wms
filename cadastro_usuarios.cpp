#include "cadastro_usuarios.h"
#include "ui_cadastro_usuarios.h"
#include "variaveis_globais.h"
#include "janela_principal.h"
#include <QMessageBox>
#include <QSqlQuery>

cadastro_usuarios::cadastro_usuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro_usuarios)
{
    ui->setupUi(this);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,100);
    QStringList cab={"ID Acesso",
"Acesso Usuário","Acesso (sim/não)"};
    ui->tableWidget->setHorizontalHeaderLabels(cab);
    //ui->tableWidget->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *cadestoq = new QTableWidgetItem();
    cadestoq->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadusu = new QTableWidgetItem();
    cadusu->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadpro = new QTableWidgetItem();
    cadpro->setCheckState(Qt::Unchecked);
    QTableWidgetItem *log = new QTableWidgetItem();
    log->setCheckState(Qt::Unchecked);
    QTableWidgetItem *transf = new QTableWidgetItem();
    transf->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadprodestoq = new QTableWidgetItem();
    cadprodestoq->setCheckState(Qt::Unchecked);
    QTableWidgetItem *lancentrestoq = new QTableWidgetItem();
    lancentrestoq->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadforn = new QTableWidgetItem();
    cadforn->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadcli = new QTableWidgetItem();
    cadcli->setCheckState(Qt::Unchecked);
    QTableWidgetItem *pedcompr = new QTableWidgetItem();
    pedcompr->setCheckState(Qt::Unchecked);
    QTableWidgetItem *cadtransp = new QTableWidgetItem();
    cadtransp->setCheckState(Qt::Unchecked);
    QTableWidgetItem *seppedid = new QTableWidgetItem();
    seppedid->setCheckState(Qt::Unchecked);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("1"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Estoques"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadestoq);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("2"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Usuários"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadusu);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Produtos"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadpro);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("4"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Entrar - Login"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,log);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("5"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Transferência - Entrada de produtos no estoque"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,transf);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("6"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Produtos no Estoque"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadprodestoq);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("7"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Lançar entrada no estoque"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,lancentrestoq);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("8"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Fornecedores"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadforn);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("9"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Clientes"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadcli);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("10"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Pedido de Compra"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,pedcompr);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("11"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Cadastro de Transportadoras"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,cadtransp);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("12"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem("Separação de Pedidos"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,seppedid);

    //ui->tableWidget->setRowHeight(3,3);


    ui->tabWidget_cadastro_usuario->setCurrentIndex(0);
    ui->cb_cad_usu_sexo->addItem("Masculino");
    ui->cb_cad_usu_sexo->addItem("Feminino");

    ui->txt_cad_usu_nome->setFocus();
    ui->txt_cad_usu_data_nasc->setInputMask("00/00/0000");
    ui->txt_cad_usu_cep->setInputMask("00000-000");
    ui->txt_cad_usu_fone->setInputMask("(00)00-00000-0000");

    QString data=QDate::currentDate().toString("dd/MM/yyyy");//Pega a data do sistema
    QString hora=QTime::currentTime().toString("hh:mm:ss");//Pega a hora do sistema
    QString cad_data = data+"-"+hora;
    //ui->txt_cad_usu_data_cadastro->setReadOnly(true);//(deletado da ui)
    //ui->txt_cad_usu_data_cadastro->setText(cad_data);//(deletado da ui)atribui a variavel com a data do sistema no qlineedit


//    ui->cb_cad_usu_tipo_usuario->addItem("A");
//    ui->cb_cad_usu_tipo_usuario->addItem("B");

    ui->tableWidget_consulta_usuario->setColumnCount(12);
    ui->tableWidget_consulta_usuario->setColumnWidth(0,50);
    ui->tableWidget_consulta_usuario->setColumnWidth(1,100);
    QStringList cabecalho={"Nome","Endereço","Tipo de usuário",
                          "Username","Fone","senha","email",
                          "pais","CEP","sexo","email alternativo",
                          "Data nasc."};
    ui->tableWidget_consulta_usuario->setHorizontalHeaderLabels(cabecalho);
    ui->tableWidget_consulta_usuario->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_consulta_usuario->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_consulta_usuario->verticalHeader()->setVisible(false);
    ui->tableWidget_consulta_usuario->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_consulta_usuario->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget_atual_usu->insertRow(3);
    ui->tableWidget_atual_usu->setItem(1,0,new QTableWidgetItem("ID Acesso"));
    ui->tableWidget_atual_usu->setItem(2,1,new QTableWidgetItem("Acesso Usuário"));
    ui->tableWidget_atual_usu->setItem(3,2,new QTableWidgetItem("Acesso (sim/não)"));
    ui->tableWidget_atual_usu->setColumnCount(3);
    ui->tableWidget_atual_usu->setColumnWidth(0,50);
    ui->tableWidget_atual_usu->setColumnWidth(1,100);
    QStringList tab_acesso={"ID Usuario","Acesso Usuário","Username"};
    ui->tableWidget_atual_usu->setHorizontalHeaderLabels(tab_acesso);
    ui->tableWidget_atual_usu->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_atual_usu->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_atual_usu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_atual_usu->verticalHeader()->setVisible(false);
    ui->tableWidget_atual_usu->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_atual_usu->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

cadastro_usuarios::~cadastro_usuarios()
{
    delete ui;
}

void cadastro_usuarios::on_btn_cadastro_usuario_clicked()
{
    QString nome_usu=ui->txt_cad_usu_nome->text();
    QString endereco_usu=ui->txt_cad_usu_endereco->text();
    //QString tipo_usu=ui->cb_cad_usu_tipo_usuario->currentText();
    QString username_usu=ui->txt_cad_usu_username->text();
    QString fone_usu=ui->txt_cad_usu_fone->text();
    QString senha_usu=ui->txt_cad_usu_senha->text();
    QString email_usu=ui->txt_cad_usu_email->text();
    QString pais_usu=ui->txt_cad_usu_pais->text();    
    QString cep_usu=ui->txt_cad_usu_cep->text();
    QString sexo_usu=ui->cb_cad_usu_sexo->currentText();
    QString email_alt_usu=ui->txt_cad_usu_email_alt->text();
    //QString data_nasc_usu=ui->txt_cad_usu_data_nasc->text();
    QString data_nasc_usu=ui->txt_cad_usu_data_nasc->text();

    int acesso_cadestoque_id=1;
    QString acesso_cadestoque ="Cadastro de Estoque";
    int acesso_cadusuario_id=2;
    QString acesso_cadusuario ="Cadastro de Usuários";
    int acesso_cadprod_id=3;
    QString acesso_cadprod ="Cadastro de Produtos";
    int acesso_login_id=4;
    QString acesso_login ="Entrar - Login";
    int acesso_transfestoq_id=5;
    QString acesso_transfestoq ="Transferência - Entrada de produtos no estoque";
    int acesso_cadprodestoq_id=6;
    QString acesso_cadprodestoq ="Cadastro de Produtos no Estoque";
    int acesso_lancestoq_id=7;
    QString acesso_lancestoq ="Lançar entrada no estoque";
    int acesso_cadforn_id=8;
    QString acesso_cadforn ="Cadastro de Fornecedores";
    int acesso_cadcli_id=9;
    QString acesso_cadcli ="Cadastro de Clientes";
    int acesso_pedcompr_id=10;
    QString acesso_pedcompr ="Pedido de Compra";
    int acesso_cadtransp_id=11;
    QString acesso_cadtransp ="Cadastro de Transportadoras";
    int acesso_sepped_id=12;
    QString acesso_sepped ="Separação de Pedidos";
    if(ui->tableWidget->item(0,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadestoque_id)+",'"+acesso_cadestoque+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(1,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadusuario_id)+",'"+acesso_cadusuario+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(2,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadprod_id)+",'"+acesso_cadprod+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(3,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_login_id)+",'"+acesso_login+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(4,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_transfestoq_id)+",'"+acesso_transfestoq+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(5,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadprodestoq_id)+",'"+acesso_cadprodestoq+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(6,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_lancestoq_id)+",'"+acesso_lancestoq+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(7,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadforn_id)+",'"+acesso_cadforn+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(8,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadcli_id)+",'"+acesso_cadcli+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(9,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_pedcompr_id)+",'"+acesso_pedcompr+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(10,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_cadtransp_id)+",'"+acesso_cadtransp+"','"+username_usu+"')");
    }


    if(ui->tableWidget->item(11,2)->checkState()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_sepped_id)+",'"+acesso_sepped+"','"+username_usu+"')");
    }

//    if(ui->cb_cad_estoque->isChecked()){
//        QSqlQuery query_tela;
//        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
//        "values ("+QString::number(acesso_tela_estoque_id)+",'"+acesso_tela_estoque+"','"+username_usu+"')");
//    }
//    if(ui->cb_cad_usuario->isChecked()){
//        QSqlQuery query_tela;
//        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
//        "values ("+QString::number(acesso_tela_usuario_id)+",'"+acesso_tela_usuario+"','"+username_usu+"')");
//    }

    QSqlQuery query;
    query.prepare("insert into tabela_usuarios (nome_usuario,endereco_usuario,username_usuario,"
                  "fone_usuario,senha_usuario,email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,"
                  "email_alternativo,data_nasc_usuario) "
                  "values ('"+nome_usu+"','"+endereco_usu+"','"+username_usu+"',"
                  "'"+fone_usu+"','"+senha_usu+"','"+email_usu+"','"+pais_usu+"',"
                  "'"+cep_usu+"','"+sexo_usu+"','"+email_alt_usu+"','"+data_nasc_usu+"' )");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar usuário");
    }else{
        QMessageBox::warning(this,"OK","Usuário cadastrado com sucesso!");
    }
}

void cadastro_usuarios::on_tabWidget_cadastro_usuario_currentChanged(int index)
{
    if(index == 1){
        while(ui->tableWidget_consulta_usuario->rowCount()>0){
            ui->tableWidget_consulta_usuario->removeRow(0);
        }
        ui->rb_filtrar_username->setChecked(true);
        ui->txt_filtrar_usuario->setFocus();
        int contlinhas = 0;
        QSqlQuery query;
        query.prepare("select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                      "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                      " from tabela_usuarios order by nome_usuario");
        if(query.exec()){
            while(query.next()){
                //O número de 0 a 12 após a variável contlinhas servem para adicionar as COLUNAS vindas da query para
                ui->tableWidget_consulta_usuario->insertRow(contlinhas);
                ui->tableWidget_consulta_usuario->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,6,new QTableWidgetItem(query.value(6).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,7,new QTableWidgetItem(query.value(7).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,8,new QTableWidgetItem(query.value(8).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,9,new QTableWidgetItem(query.value(9).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,10,new QTableWidgetItem(query.value(10).toString()));
                ui->tableWidget_consulta_usuario->setItem(contlinhas,11,new QTableWidgetItem(query.value(11).toString()));
                ui->tableWidget_consulta_usuario->setRowHeight(contlinhas,12);
                contlinhas++;
            }
        }else{
            QMessageBox::warning(this,"ERRO","Erro ao listar usuários");
        }
    }
}

void cadastro_usuarios::on_btn_filtrar_usuario_clicked()
{
    QString busca;
    while(ui->tableWidget_consulta_usuario->rowCount()>0){
        ui->tableWidget_consulta_usuario->removeRow(0);
    }
    if(ui->txt_filtrar_usuario->text()==""){
        if(ui->rb_filtrar_cep->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by cep_end_usuario";
        }else if(ui->rb_filtrar_email->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by email_usuario";
        }else if(ui->rb_filtrar_fone->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by fone_usuario";
        }else if(ui->rb_filtrar_nome->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by nome_usuario";
        }else if(ui->rb_filtrar_sexo->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by sexo_usuario";
        }else if(ui->rb_filtrar_username->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by username_usuario";
        }
    }else if(ui->txt_filtrar_usuario->text()!=""){
        if(ui->rb_filtrar_cep->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where cep_end_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by cep_end_usuario";
        }else if(ui->rb_filtrar_email->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where email_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by email_usuario";
        }else if(ui->rb_filtrar_fone->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where fone_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by fone_usuario";
        }else if(ui->rb_filtrar_nome->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where nome_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by nome_usuario";
        }else if(ui->rb_filtrar_sexo->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where sexo_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by sexo_usuario";
        }else if(ui->rb_filtrar_username->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where username_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by username_usuario";
        }
    }

    int contlinhas=0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec()){
        while(query.next()){
            ui->tableWidget_consulta_usuario->insertRow(contlinhas);
            ui->tableWidget_consulta_usuario->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,8,new QTableWidgetItem(query.value(8).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,9,new QTableWidgetItem(query.value(9).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,10,new QTableWidgetItem(query.value(10).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,11,new QTableWidgetItem(query.value(11).toString()));
            ui->tableWidget_consulta_usuario->setRowHeight(contlinhas,12);
            contlinhas++;
        }
    }else{
        QMessageBox::warning(this,"Erro!","Erro ao filtrar usuários do sistema!");
    }
    ui->txt_filtrar_usuario->clear();
    ui->txt_filtrar_usuario->setFocus();
}

void cadastro_usuarios::on_txt_filtrar_usuario_returnPressed()
{
    QString busca;
    while(ui->tableWidget_consulta_usuario->rowCount()>0){
        ui->tableWidget_consulta_usuario->removeRow(0);
    }
    if(ui->txt_filtrar_usuario->text()==""){
        if(ui->rb_filtrar_cep->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by cep_end_usuario";
        }else if(ui->rb_filtrar_email->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by email_usuario";
        }else if(ui->rb_filtrar_fone->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by fone_usuario";
        }else if(ui->rb_filtrar_nome->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by nome_usuario";
        }else if(ui->rb_filtrar_sexo->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by sexo_usuario";
        }else if(ui->rb_filtrar_username->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios order by username_usuario";
        }
    }else if(ui->txt_filtrar_usuario->text()!=""){
        if(ui->rb_filtrar_cep->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where cep_end_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by cep_end_usuario";
        }else if(ui->rb_filtrar_email->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where email_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by email_usuario";
        }else if(ui->rb_filtrar_fone->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where fone_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by fone_usuario";
        }else if(ui->rb_filtrar_nome->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where nome_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by nome_usuario";
        }else if(ui->rb_filtrar_sexo->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where sexo_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by sexo_usuario";
        }else if(ui->rb_filtrar_username->isChecked()){
            busca="select nome_usuario,endereco_usuario,tipo_usuario,username_usuario,fone_usuario,senha_usuario,"
                  "email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,email_alternativo,data_nasc_usuario"
                  " from tabela_usuarios where username_usuario like '%"+ui->txt_filtrar_usuario->text()+"%' order by username_usuario";
        }
    }

    int contlinhas=0;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec()){
        while(query.next()){
            ui->tableWidget_consulta_usuario->insertRow(contlinhas);
            ui->tableWidget_consulta_usuario->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,8,new QTableWidgetItem(query.value(8).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,9,new QTableWidgetItem(query.value(9).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,10,new QTableWidgetItem(query.value(10).toString()));
            ui->tableWidget_consulta_usuario->setItem(contlinhas,11,new QTableWidgetItem(query.value(11).toString()));
            ui->tableWidget_consulta_usuario->setRowHeight(contlinhas,12);
            contlinhas++;
        }
    }else{
        QMessageBox::warning(this,"Erro!","Erro ao filtrar usuários do sistema!");
    }
    ui->txt_filtrar_usuario->clear();
    ui->txt_filtrar_usuario->setFocus();
}


void cadastro_usuarios::on_btn_excluir_usuario_clicked()
{
    if(ui->tableWidget_consulta_usuario->currentColumn()!=-1){
        int row=ui->tableWidget_consulta_usuario->currentRow();
        QString username=ui->tableWidget_consulta_usuario->item(row,3)->text();
        QString nome=ui->tableWidget_consulta_usuario->item(row,0)->text();
        QMessageBox::StandardButton opc=QMessageBox::question(this,"Deseja excluir?","Confirma excluir o usuário selecionado?\nusuário: "+username,
QMessageBox::Yes|QMessageBox::No);
        if(opc==QMessageBox::Yes){
            QSqlQuery query;
            query.prepare("delete from tabela_usuarios where "
" nome_usuario ='"+nome+"' and username_usuario ='"+username+"' ");
            if(query.exec()){
                ui->tableWidget_consulta_usuario->removeRow(ui->tableWidget_consulta_usuario->currentRow());
                QMessageBox::warning(this,"Excluído!","O usuário "+username+"\nfoi excluído com sucesso!");
            }else{
                QMessageBox::warning(this,"Erro","Não foi possível deletar!");
            }
        }
    }else{
        QMessageBox::warning(this,"Erro","Selecione um usuário primeiro!");
    }
}

void cadastro_usuarios::on_btn_editar_usuario_clicked()
{
    int row=ui->tableWidget_consulta_usuario->currentRow();
    if(!ui->tableWidget_consulta_usuario->currentItem()){
        QMessageBox::warning(this,"Erro","Selecione um usuário primeiro!");
    }else{
        QString username=ui->tableWidget_consulta_usuario->item(row,3)->text();
        QMessageBox::StandardButton opc=QMessageBox::question(this,"Deseja Editar?","Confirma editar o usuário selecionado?\nusuário: "+username,
    QMessageBox::Yes|QMessageBox::No);
        if(opc==QMessageBox::Yes){
            while(ui->tableWidget_atual_usu->rowCount()>0){
                ui->tableWidget_atual_usu->removeRow(0);
            }
            QSqlQuery query_usuario,query_acesso_usu;
            query_usuario.exec("select * from tabela_usuarios where username_usuario "
        " = '"+username+"' order by username_usuario ");
            query_usuario.first();
            ui->txt_atual_usu_nome->setText(query_usuario.value(1).toString());
            ui->txt_atual_usu_username->setText(query_usuario.value(4).toString());
            ui->txt_atual_usu_senha->setText(query_usuario.value(6).toString());
            ui->txt_atual_usu_cep->setText(query_usuario.value(9).toString());
            ui->txt_atual_usu_endereco->setText(query_usuario.value(2).toString());
            ui->txt_atual_usu_fone->setText(query_usuario.value(5).toString());
            ui->cb_atual_usu_tipo_usuario->setCurrentIndex(0);
            ui->cb_atual_usu_sexo->setCurrentIndex(0);
            ui->txt_atual_usu_email->setText(query_usuario.value(7).toString());
            ui->txt_atual_usu_email_alt->setText(query_usuario.value(11).toString());
            ui->txt_atual_usu_data_nasc->setText(query_usuario.value(13).toString());
            ui->txt_atual_usu_pais->setText(query_usuario.value(8).toString());
            query_acesso_usu.exec("select * from acesso_usuarios where username_usuario "
        " = 'adm' order by id_acesso_usuario ");
            query_acesso_usu.first();
            if(query_acesso_usu.value(1).toString()!=""){
                do{
                    int cont=ui->tableWidget_atual_usu->rowCount();
                    ui->tableWidget_atual_usu->insertRow(cont);
                    QTableWidgetItem *acesso = new QTableWidgetItem(query_acesso_usu.value(2).toString());
                    acesso->setCheckState(Qt::Unchecked);
                    ui->tableWidget_atual_usu->setItem(cont,0,new QTableWidgetItem(query_acesso_usu.value(0).toString()));
                    ui->tableWidget_atual_usu->setItem(cont,1,new QTableWidgetItem(query_acesso_usu.value(1).toString()));
                    ui->tableWidget_atual_usu->setItem(cont,2,acesso);
                }while(query_acesso_usu.next());
            }
        }else{
            QMessageBox::warning(this,"Erro","Selecione um usuário primeiro!");
        }
    }
}

void cadastro_usuarios::on_btn_atual_cancelar_clicked()
{

}

void cadastro_usuarios::on_btn_atualizar_usuario_clicked()
{

}
