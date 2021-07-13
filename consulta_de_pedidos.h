#ifndef CONSULTA_DE_PEDIDOS_H
#define CONSULTA_DE_PEDIDOS_H

#include <QDialog>

namespace Ui {
class consulta_de_pedidos;
}

class consulta_de_pedidos : public QDialog
{
    Q_OBJECT

public:
    explicit consulta_de_pedidos(QWidget *parent = nullptr);
    ~consulta_de_pedidos();

private:
    Ui::consulta_de_pedidos *ui;
};

#endif // CONSULTA_DE_PEDIDOS_H
