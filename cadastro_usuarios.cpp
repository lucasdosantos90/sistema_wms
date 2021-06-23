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
    ui->txt_cad_usu_data_cadastro->setReadOnly(true);
    ui->txt_cad_usu_data_cadastro->setText(cad_data);//atribui a variavel com a data do sistema no qlineedit


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

    int acesso_tela_estoque_id=1;
    QString acesso_tela_estoque ="Cadastro de Estoque";

    int acesso_tela_usuario_id=2;
    QString acesso_tela_usuario ="Cadastro de Usuários";

    if(ui->cb_cad_estoque->isChecked()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_tela_estoque_id)+",'"+acesso_tela_estoque+"','"+username_usu+"')");
    }
    if(ui->cb_cad_usuario->isChecked()){
        QSqlQuery query_tela;
        query_tela.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
        "values ("+QString::number(acesso_tela_usuario_id)+",'"+acesso_tela_usuario+"','"+username_usu+"')");
    }

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
