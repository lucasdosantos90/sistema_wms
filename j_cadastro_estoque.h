#ifndef J_CADASTRO_ESTOQUE_H
#define J_CADASTRO_ESTOQUE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class j_cadastro_estoque;
}

class j_cadastro_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit j_cadastro_estoque(QWidget *parent = nullptr);
    ~j_cadastro_estoque();
    QSqlDatabase banco_de_dados=QSqlDatabase::addDatabase("QSQLITE");
private slots:
    void on_btn_cad_estoque_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::j_cadastro_estoque *ui;
};

#endif // J_CADASTRO_ESTOQUE_H
