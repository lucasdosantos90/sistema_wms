#ifndef LANCAR_ENTRADA_NO_ESTOQUE_H
#define LANCAR_ENTRADA_NO_ESTOQUE_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include "conexao.h"
namespace Ui {
class lancar_entrada_no_estoque;
}

class lancar_entrada_no_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit lancar_entrada_no_estoque(QWidget *parent = nullptr);
    ~lancar_entrada_no_estoque();
    Conexao con;

private slots:

    void on_txt_add_qtde_produto_returnPressed();

    void on_txt_local_estoque_returnPressed();

    void on_txt_add_produto_returnPressed();

    void on_tableWidget_local_estoque_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

    void on_btn_lancar_estoque_clicked();

private:
    Ui::lancar_entrada_no_estoque *ui;
};

#endif // LANCAR_ENTRADA_NO_ESTOQUE_H
