#include "consulta_de_pedidos.h"
#include "ui_consulta_de_pedidos.h"

consulta_de_pedidos::consulta_de_pedidos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consulta_de_pedidos)
{
    ui->setupUi(this);
}

consulta_de_pedidos::~consulta_de_pedidos()
{
    delete ui;
}
