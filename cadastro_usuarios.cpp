#include "cadastro_usuarios.h"
#include "ui_cadastro_usuarios.h"
#include "variaveis_globais.h"
#include "janela_principal.h"
#include <QMessageBox>
#include <QSqlQuery>

QStringList texto_janelas={"Cadastro de Estoques","Cadastro de Usuários",
"Cadastro de Produtos","Entrar - Login","Transferência - Entrada de produtos no estoque",
"Cadastro de Produtos no Estoque","Lançar entrada no estoque","Cadastro de Fornecedores",
"Cadastro de Clientes","Pedido de Compra","Cadastro de Transportadoras",
"Separação de Pedidos","Consulta de Pedidos"};

QStringList funcoes_usuarios={"CEO","Administrador","Gerente Geral","Gerente",
"Encarregado","Vendedor","Vendedor-A","Vendedor-B","Vendedor-C","Técnico-A",
"Técnico-B","Técnico-C","Operador-A","Operador-B","Operador-C"};

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

    //inicializando a QStringList para declarar nome das janelas do sistema
    //e um for para preencher as janelas com os nomes das janelas

    int num=1;
    for(int i=0;i<texto_janelas.size();i++){
        QTableWidgetItem *janelas = new QTableWidgetItem();
        janelas->setCheckState(Qt::Unchecked);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(num)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(texto_janelas[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,janelas);
        num++;
    }

    //ui->tableWidget->setRowHeight(3,3);


    ui->tabWidget_cadastro_usuario->setCurrentIndex(0);
    for(int i=0;i<funcoes_usuarios.size();i++){
        ui->cb_cad_usu_tipo_usuario->addItem(funcoes_usuarios[i]);
    }
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


//    ui->usu_tipo_usuario->addItem("A");
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

    ui->tableWidget_atual_usu->setColumnCount(3);
    ui->tableWidget_atual_usu->setColumnWidth(0,50);
    ui->tableWidget_atual_usu->setColumnWidth(1,100);
    QStringList tab_acesso={"ID","Acesso Usuário","Username"};
    ui->tableWidget_atual_usu->setHorizontalHeaderLabels(tab_acesso);
    ui->tableWidget_atual_usu->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_atual_usu->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_atual_usu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_atual_usu->verticalHeader()->setVisible(false);
    ui->tableWidget_atual_usu->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_atual_usu->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget_total->insertRow(3);
    ui->tableWidget_total->setItem(1,0,new QTableWidgetItem("ID"));
    ui->tableWidget_total->setItem(2,1,new QTableWidgetItem("Acesso Usuário"));
    ui->tableWidget_total->setItem(3,2,new QTableWidgetItem("Username"));
    ui->tableWidget_total->setColumnCount(3);
    ui->tableWidget_total->setColumnWidth(0,50);
    ui->tableWidget_total->setColumnWidth(1,100);
    QStringList tab_acesso_total={"ID","Acesso Usuário","Username"};
    ui->tableWidget_total->setHorizontalHeaderLabels(tab_acesso_total);
    ui->tableWidget_total->setStyleSheet("QTableView {selection-background-color:blue}");
    ui->tableWidget_total->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_total->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_total->verticalHeader()->setVisible(false);
    ui->tableWidget_total->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_total->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

cadastro_usuarios::~cadastro_usuarios()
{
    delete ui;
}

void cadastro_usuarios::on_btn_cadastro_usuario_clicked()
{
    QString nome_usu=ui->txt_cad_usu_nome->text();
    QString endereco_usu=ui->txt_cad_usu_endereco->text();
    QString tipo_usu=ui->cb_cad_usu_tipo_usuario->currentText();
    QString username_usu=ui->txt_cad_usu_username->text();
    QString fone_usu=ui->txt_cad_usu_fone->text();
    QString senha_usu=ui->txt_cad_usu_senha->text();
    QString email_usu=ui->txt_cad_usu_email->text();
    QString pais_usu=ui->txt_cad_usu_pais->text();    
    QString cep_usu=ui->txt_cad_usu_cep->text();
    QString sexo_usu=ui->cb_cad_usu_sexo->currentText();
    QString email_alt_usu=ui->txt_cad_usu_email_alt->text();
    QString data_nasc_usu=ui->txt_cad_usu_data_nasc->text();

    QSqlQuery query;
    query.prepare("insert into tabela_usuarios (nome_usuario,endereco_usuario,tipo_usuario,username_usuario,"
                  "fone_usuario,senha_usuario,email_usuario,pais_origem_usuario,cep_end_usuario,sexo_usuario,"
                  "email_alternativo,data_nasc_usuario) "
                  "values ('"+nome_usu+"','"+endereco_usu+"','"+tipo_usu+"','"+username_usu+"',"
                  "'"+fone_usu+"','"+senha_usu+"','"+email_usu+"','"+pais_usu+"',"
                  "'"+cep_usu+"','"+sexo_usu+"','"+email_alt_usu+"','"+data_nasc_usu+"' )");
    if(!query.exec()){
        QMessageBox::warning(this,"ERRO","Erro ao cadastrar usuário");
    }else{
        int id=1;
        for(int n=0;n<texto_janelas.size();n++){
            if(ui->tableWidget->item(n,2)->checkState()){
                QSqlQuery query_acesso;
                query_acesso.exec("insert into acesso_usuarios (id_acesso_usuario,acesso_usuario,username_usuario)"
                "values ("+QString::number(id)+",'"+ui->tableWidget->item(n,1)->text()+"','"+username_usu+"')");
                id++;
            }
        }
        QMessageBox::warning(this,"OK","Usuário cadastrado com sucesso!");
    }

}

void cadastro_usuarios::on_tabWidget_cadastro_usuario_currentChanged(int index)
{
    if(index == 1){
        while(ui->tableWidget_consulta_usuario->rowCount()>0){
            ui->tableWidget_consulta_usuario->removeRow(0);
        }
        while(ui->tableWidget_total->rowCount()>0){
            ui->tableWidget_total->removeRow(0);
        }
        for(int i=0;i<funcoes_usuarios.size();i++){
            ui->cb_atual_usu_tipo_usuario->addItem(funcoes_usuarios[i]);
        }
        ui->cb_atual_usu_sexo->addItem("Masculino");
        ui->cb_atual_usu_sexo->addItem("Feminino");
        ui->txt_atual_usu_data_nasc->setInputMask("00/00/0000");
        ui->txt_atual_usu_cep->setInputMask("00000-000");
        ui->txt_atual_usu_fone->setInputMask("(00)00-00000-0000");
        ui->rb_filtrar_username->setChecked(true);
        ui->txt_filtrar_usuario->setFocus();
        int contlinhas = 0;
        QSqlQuery query,query_acesso_usu;
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
            query_acesso_usu.exec("select * from acesso_usuarios where username_usuario "
        " = 'adm' order by id_acesso_usuario ");
            query_acesso_usu.first();
            if(query_acesso_usu.value(1).toString()!=""){
                do{
                    int cont=ui->tableWidget_total->rowCount();
                    ui->tableWidget_total->insertRow(cont);
                    QTableWidgetItem *acesso = new QTableWidgetItem();
                    //acesso->setCheckState(Qt::Unchecked);
                    ui->tableWidget_total->setItem(cont,0,new QTableWidgetItem(query_acesso_usu.value(0).toString()));
                    ui->tableWidget_total->setItem(cont,1,new QTableWidgetItem(query_acesso_usu.value(1).toString()));
                    ui->tableWidget_total->setItem(cont,2,acesso);
                }while(query_acesso_usu.next());
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
            while(ui->tableWidget_total->rowCount()>0){
                ui->tableWidget_total->removeRow(0);
            }
            while(ui->tableWidget_atual_usu->rowCount()>0){
                ui->tableWidget_atual_usu->removeRow(0);
            }
            QSqlQuery query_usuario,query_acesso_usu,query_acesso;
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
            query_acesso.exec("select * from acesso_usuarios where username_usuario "
        " = '"+username+"' order by id_acesso_usuario ");
            query_acesso_usu.first();
            query_acesso.first();
            if(query_acesso_usu.value(1).toString()!=""){
                int num=1;
                for(int i=0;i<texto_janelas.size();i++){
                    ui->tableWidget_total->insertRow(ui->tableWidget_total->rowCount());
                    ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount()-1,0,new QTableWidgetItem(QString::number(num)));
                    ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount()-1,1,new QTableWidgetItem(texto_janelas[i]));
                    ui->tableWidget_total->setItem(ui->tableWidget_total->rowCount()-1,2,new QTableWidgetItem(username));
                    num++;
                }
                if(query_acesso.value(1).toString()!=""){
                    do{
                        int cont=ui->tableWidget_atual_usu->rowCount();
                        ui->tableWidget_atual_usu->insertRow(cont);
                        ui->tableWidget_atual_usu->setItem(cont,0,new QTableWidgetItem(query_acesso.value(0).toString()));
                        ui->tableWidget_atual_usu->setItem(cont,1,new QTableWidgetItem(query_acesso.value(1).toString()));
                        ui->tableWidget_atual_usu->setItem(cont,2,new QTableWidgetItem(query_acesso.value(2).toString()));
                    }while(query_acesso.next());
                }
            }
        }else{
            QMessageBox::warning(this,"Erro","Selecione um usuário primeiro!");
        }
    }
}

void cadastro_usuarios::on_btn_atualizar_usuario_clicked()
{
    if(!ui->tableWidget_consulta_usuario->currentItem()){
        QMessageBox::warning(this,"Erro","Selecione um usuário primeiro!");
    }else{
        QString username=ui->txt_atual_usu_username->text();
        QMessageBox::StandardButton opc=QMessageBox::question(this,"Confirma?","Confirma Atualizar o usuário selecionado?\nusuário: "+username,
    QMessageBox::Yes|QMessageBox::No);
        if(opc==QMessageBox::Yes){
            QString atual_nome=ui->txt_atual_usu_nome->text();
            QString atual_user=ui->txt_atual_usu_username->text();
            QString atual_senha=ui->txt_atual_usu_senha->text();
            QString atual_cep=ui->txt_atual_usu_senha->text();
            QString atual_end=ui->txt_atual_usu_endereco->text();
            QString atual_fone=ui->txt_atual_usu_endereco->text();
            QString atual_tipo=ui->cb_atual_usu_tipo_usuario->currentText();
            QString atual_sexo=ui->cb_atual_usu_sexo->currentText();
            QString atual_email=ui->txt_atual_usu_email->text();
            QString atual_email_alt=ui->txt_atual_usu_email_alt->text();
            QString atual_data_nasc=ui->txt_atual_usu_data_nasc->text();
            QString atual_pais=ui->txt_atual_usu_pais->text();

            QSqlQuery query_atual_usu;
    query_atual_usu.exec("update tabela_usuarios set nome_usuario ='"+atual_nome+"', "
    " endereco_usuario ='"+atual_end+"',tipo_usuario ='"+atual_tipo+"', "
    " username_usuario ='"+atual_user+"',fone_usuario ='"+atual_fone+"', "
    " senha_usuario ='"+atual_senha+"',email_usuario ='"+atual_email+"', "
    " pais_origem_usuario ='"+atual_pais+"',cep_end_usuario ='"+atual_cep+"', "
    " sexo_usuario ='"+atual_sexo+"',email_alternativo ='"+atual_email_alt+"', "
    " data_nasc_usuario ='"+atual_data_nasc+"',data_nasc_usuario ='"+atual_data_nasc+"'"
    " where username_usuario ='"+atual_user+"' ");

            if(!query_atual_usu.exec()){
                QMessageBox::warning(this,"ERRO","Erro ao atualizar usuário");
            }else{
                QSqlQuery query_ac,query_del;
                int cont=0;
                int total_ac=ui->tableWidget_atual_usu->rowCount();
                query_del.exec("delete from acesso_usuarios "
    " where username_usuario ='"+atual_user+"' ");
                while(cont<total_ac){
                    int id_ac=ui->tableWidget_atual_usu->item(cont,0)->text().toInt();
                    QString nome_ac=ui->tableWidget_atual_usu->item(cont,1)->text();
                    QString user_ac=ui->tableWidget_atual_usu->item(cont,2)->text();

                    query_ac.prepare("insert into acesso_usuarios "
    " (id_acesso_usuario,acesso_usuario,username_usuario) values "
    " ("+QString::number(id_ac)+",'"+nome_ac+"','"+user_ac+"') ");
                    query_ac.exec();
                    cont++;
                }
                    QMessageBox::warning(this,"Atualizado!","Usuário atualizado com sucesso!");
            }
        }
    }
}

void cadastro_usuarios::on_btn_add_acesso_clicked()
{
    int cont_compara=0;
    int curr_item=ui->tableWidget_total->currentRow();
    if(!ui->tableWidget_total->currentItem()){
        QMessageBox::warning(this,"Erro","Nenhum acesso selecionado!");
    }else{
        if(ui->tableWidget_atual_usu->rowCount()>0){
            while(cont_compara<ui->tableWidget_atual_usu->rowCount()){
                if(ui->tableWidget_total->item(curr_item,1)->text()==ui->tableWidget_atual_usu->item(cont_compara,1)->text()){
                    QMessageBox::warning(this,"Erro","acesso já cadastrado!");
                    goto fim;
                }
            cont_compara++;
            }
        }
            int row=ui->tableWidget_total->currentRow();
            QString id=ui->tableWidget_total->item(row,0)->text();
            QString acesso=ui->tableWidget_total->item(row,1)->text();
            QString username=ui->tableWidget_total->item(row,2)->text();
            int cont_add=0;
            ui->tableWidget_atual_usu->insertRow(cont_add);
            ui->tableWidget_atual_usu->setItem(cont_add,0,new QTableWidgetItem(id));
            ui->tableWidget_atual_usu->setItem(cont_add,1,new QTableWidgetItem(acesso));
            ui->tableWidget_atual_usu->setItem(cont_add,2,new QTableWidgetItem(username));
            ui->tableWidget_atual_usu->setRowHeight(cont_add,3);
    }
    fim:;
}

void cadastro_usuarios::on_btn_excluir_acesso_clicked()
{
    if(!ui->tableWidget_atual_usu->currentItem()){
        QMessageBox::warning(this,"Erro","Nenhum acesso selecionado!");
    }else{
        ui->tableWidget_atual_usu->removeRow(ui->tableWidget_atual_usu->currentRow());
        ui->tableWidget_atual_usu->selectRow(0);
    }
}

void cadastro_usuarios::on_btn_cancelar_clicked()
{
    ui->txt_cad_usu_nome->setText("");
    ui->txt_cad_usu_username->setText("");
    ui->txt_cad_usu_senha->setText("");
    ui->txt_cad_usu_cep->setText("");
    ui->txt_cad_usu_endereco->setText("");
    ui->txt_cad_usu_fone->setText("");
    ui->txt_cad_usu_email->setText("");
    ui->txt_cad_usu_email_alt->setText("");
    ui->txt_cad_usu_data_nasc->setText("");
    ui->txt_cad_usu_pais->setText("");
    ui->cb_cad_usu_sexo->setCurrentIndex(0);
    ui->cb_cad_usu_tipo_usuario->setCurrentIndex(0);
    ui->txt_cad_usu_nome->setFocus();
}
