#ifndef CADASTRO_USUARIOS_H
#define CADASTRO_USUARIOS_H

#include <QDialog>
#include <QSqlQuery>
#include "conexao.h"

namespace Ui {
class cadastro_usuarios;
}

class cadastro_usuarios : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_usuarios(QWidget *parent = nullptr);
    ~cadastro_usuarios();
    Conexao con;

private slots:
    void on_btn_cadastro_usuario_clicked();

    void on_tabWidget_cadastro_usuario_currentChanged(int index);

    void on_btn_filtrar_usuario_clicked();

    void on_txt_filtrar_usuario_returnPressed();

    void on_btn_excluir_usuario_clicked();

    void on_btn_editar_usuario_clicked();

    void on_btn_atualizar_usuario_clicked();

    void on_btn_add_acesso_clicked();

    void on_btn_excluir_acesso_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::cadastro_usuarios *ui;
};

#endif // CADASTRO_USUARIOS_H
