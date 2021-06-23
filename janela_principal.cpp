#include "janela_principal.h"
#include "ui_janela_principal.h"
#include "cadastro_usuarios.h"
#include "janela_login.h"
#include "cadastro_estoque.h"
#include "variaveis_globais.h"
#include "cadastro_produtos.h"
#include "entrada_produtos_estoque.h"
#include "cadastro_de_produtos_no_estoque.h"
#include "lancar_entrada_no_estoque.h"
#include "cadastro_de_fornecedores.h"
#include "cadastro_de_clientes.h"
#include "cadastro_de_transportadoras.h"
#include "separacao_de_pedidos.h"
#include "pedido_de_compra.h"
#include "conexao.h"
#include <QMdiSubWindow>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QGridLayout>
#include <QLabel>
#include <QGridLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QScreen>

QString variaveis_globais::acesso;
QString variaveis_globais::nome;
QString variaveis_globais::username;
bool variaveis_globais::logado;

janela_principal::janela_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::janela_principal)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    setCentralWidget(ui->mdiArea);
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    if(con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados!");
        }
    }

    ui->label_nome->setText(variaveis_globais::nome);
    ui->label_username->setText(variaveis_globais::username);
    ui->label_tipo->setText(variaveis_globais::acesso);

    ui->mdiArea->currentSubWindow()->setWindowTitle(variaveis_globais::username);
    //ui->mdiArea->currentSubWindow()->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    Qt::WindowFlags flags = ui->mdiArea->currentSubWindow()->windowFlags();
    flags |= Qt::CustomizeWindowHint;
    //flags &= ~Qt::WindowContextHelpButtonHint;
    flags &= ~Qt::WindowSystemMenuHint;
    flags &= ~Qt::WindowMinMaxButtonsHint;
    //flags &= ~Qt::WindowCloseButtonHint;
    ui->mdiArea->currentSubWindow()->setWindowFlags(flags);

    ui->treeWidget->setColumnCount(2);
    addroot(variaveis_globais::username,"ID");


//    //DEIXA O HEADER ESCONDIDO!
//    //-------------------------------------
//    ui->treeWidget->setHeaderHidden(true);
//    //-------------------------------------

//    //this->window()->setMinimumSize(600,300);
//    window()->showMaximized();
//    window()->setWindowTitle("Meu sistema WMS - Janela Principal");

//    this->setCentralWidget(ui->treeWidget);//Coloca o tamanho do widget igual ao da janela
}

janela_principal::~janela_principal()
{
    delete ui;
}

void janela_principal::loadsubwindow(QWidget *widget)
{
    auto window = ui->mdiArea->addSubWindow(widget,Qt::SubWindow);
    //auto jan = ui->mdiArea->addSubWindow(widget,Qt::SubWindow);
//    window->setWindowTitle(widget->windowTitle());
//    window->setWindowIcon(widget->windowIcon());
//    window->setWindowFlags( Qt::WindowTitleHint /*|  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint*/);
//    window->setFixedSize(400,400);
    //window->show();
}

void janela_principal::addroot(QString nome,QString descricao)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,nome);
    ui->treeWidget->addTopLevelItem(itm);

    addchild(itm,0,variaveis_globais::username);

}

void janela_principal::addchild(QTreeWidgetItem *parent,QString id, QString nome/*,QString descricao*/)
{
    con.abrir();

    QSqlQuery tree_query;
    tree_query.prepare("select * from acesso_usuarios where username_usuario='"+variaveis_globais::username+"' order by id_acesso_usuario");
    tree_query.exec();
    //tree_query.first();
    while(tree_query.next())
    {
    QTreeWidgetItem *itm_id = new QTreeWidgetItem();
        id=tree_query.value(1).toString();
        itm_id->setText(0,id);
        parent->addChild(itm_id);

        id=tree_query.value(0).toString();
        itm_id->setText(1,id);
        parent->addChild(itm_id);

        //ADICIONA O ID - FUNCIONANDO! - MAS NAO CONSEGUI DAR HIDE
        //PARA CHAMAR DEPOIS NO SWITCH CASE, NO DOUBLE CLICK
        //        id=tree_query.value(0).toString();
        //        itm_id->setText(0,id);
        //        parent->addChild(itm_id);
    }


    //DEIXA O ID NA TREE ESCONDIDO!
    //-------------------------------------
    ui->treeWidget->setColumnHidden(1,true);//DEIXA O ID NA TREE ESCONDIDO!
    //-------------------------------------

    //DEIXA O HEADER ESCONDIDO!
    //-------------------------------------
    ui->treeWidget->setHeaderHidden(true);//DEIXA O HEADER ESCONDIDO!
    //-------------------------------------
    con.fechar();
}

void janela_principal::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //------------------------------------------
    //------------------------------------------
    //SWITCH CASE PARA ABRIR TODAS AS TELAS
    //      PUXADAS DO BANCO DE DADOS
    //------------------------------------------
    //------------------------------------------
    int item_compare = 0;
    item_compare=item->text(1).toInt();
    //QString item_string = item->text(0);
    switch(item_compare)
    {
    case 1:
        {
            QString item_string = item->text(0);
            cadastro_estoque *j = new cadastro_estoque(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(800,600);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        break;
        }
    case 2:
        {
            QString item_string = item->text(0);
            cadastro_usuarios *j = new cadastro_usuarios(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(571,517);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        break;
        }
    case 3:
        {
            QString item_string = item->text(0);
            cadastro_produtos *j = new cadastro_produtos(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(575,469);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        break;
        }
    case 4:
        {
            QString item_string = item->text(0);
            janela_login *j = new janela_login(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(400,300);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        break;
        }
    case 5:
        {
            QString item_string = item->text(0);
            entrada_produtos_estoque *j = new entrada_produtos_estoque(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(704,584);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
    case 6:
        {
            QString item_string = item->text(0);
            cadastro_de_produtos_no_estoque *j = new cadastro_de_produtos_no_estoque(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(734,661);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
    case 7:
        {
            QString item_string = item->text(0);
            lancar_entrada_no_estoque *j = new lancar_entrada_no_estoque(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(595,468);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
    case 8:
        {
            QString item_string = item->text(0);
            cadastro_de_fornecedores *j = new cadastro_de_fornecedores(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(772,523);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
     case 9:
        {
            QString item_string = item->text(0);
            cadastro_de_clientes *j = new cadastro_de_clientes(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(777,518);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
     case 10:
        {
            QString item_string = item->text(0);
            pedido_de_compra *j = new pedido_de_compra(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(760,606);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
     case 11:
        {
            QString item_string = item->text(0);
            cadastro_de_transportadoras *j = new cadastro_de_transportadoras(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(774,529);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
    case 12:
        {
            QString item_string = item->text(0);
            separacao_de_pedidos *j = new separacao_de_pedidos(ui->mdiArea);
            j->setWindowTitle(item_string);
            j->setFixedSize(1000,560);
            QGridLayout *gridLayout = new QGridLayout(j);
            j->setLayout(gridLayout);
            Qt::WindowFlags flags = j->window()->windowFlags();
            flags |= Qt::CustomizeWindowHint;
            flags &= ~Qt::WindowContextHelpButtonHint;
            //flags &= ~Qt::WindowSystemMenuHint;
            //flags &= ~Qt::WindowMinMaxButtonsHint;
            //flags &= ~Qt::WindowMinimizeButtonHint;
            flags &= ~Qt::WindowMinimized;
            flags &= ~Qt::WindowCloseButtonHint;
            ui->mdiArea->addSubWindow(j)->setWindowFlags(flags);
            ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            j->show();
        }
        break;
    default:
        //QMessageBox::information(this,"Erro","Link da tela não foi preenchido\n ou não existe!");
        break;
    }
}

