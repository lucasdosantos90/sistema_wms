#ifndef CADASTRO_DE_PRODUTOS_NO_ESTOQUE_H
#define CADASTRO_DE_PRODUTOS_NO_ESTOQUE_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include "conexao.h"

namespace Ui {
class cadastro_de_produtos_no_estoque;
}

class cadastro_de_produtos_no_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_de_produtos_no_estoque(QWidget *parent = nullptr);
    ~cadastro_de_produtos_no_estoque();
    Conexao con;
private slots:    
    void on_txt_add_prod_returnPressed();

    void on_pushButton_clicked();

    void on_btn_cad_prod_estoque_clicked();

    void on_tableWidget_estoq_disp_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_estoq_disp_itemSelectionChanged();

    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_consulta_estoque_itemClicked(QTableWidgetItem *item);

private:
    Ui::cadastro_de_produtos_no_estoque *ui;
};

#endif // CADASTRO_DE_PRODUTOS_NO_ESTOQUE_H
