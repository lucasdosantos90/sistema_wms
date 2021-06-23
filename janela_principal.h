#ifndef JANELA_PRINCIPAL_H
#define JANELA_PRINCIPAL_H

#include <QMainWindow>
#include <QSqlQuery>
#include "conexao.h"

#include <QtCore>//QtreeWidget
#include <QtGui>//QtreeWidget
#include <QDialog>//QtreeWidget
#include <QTreeWidgetItem>//QtreeWidget

#include <QHBoxLayout>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class janela_principal; }
QT_END_NAMESPACE

class janela_principal : public QMainWindow
{
    Q_OBJECT

    void addroot(QString nome,QString descricao);
    void addchild(QTreeWidgetItem *parent,QString id, QString nome/*,QString descricao*/);

public:
    janela_principal(QWidget *parent = nullptr);
    ~janela_principal();
    Conexao con;
private slots:
    void loadsubwindow(QWidget *widget);
    //QMdiArea * mdiArea;//CUIDADO! - DANDO CRASH NO SISTEMA AO USAR

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::janela_principal *ui;
};
#endif // JANELA_PRINCIPAL_H
