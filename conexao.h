#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao{
public:
    QSqlDatabase bancoDeDados;
    QString local;
    QString banco;
    Conexao(){
        local=qApp->applicationDirPath();
        banco=local+"/BD/Sistema_de_estoque_WMS.db";
        bancoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    }
    void fechar(){
        bancoDeDados.close();
    }
    bool abrir(){
        bancoDeDados.setDatabaseName(banco);
        if(!bancoDeDados.open()){
            return false;
        }else{
            return true;
        }
    }
    bool aberto(){
        if(bancoDeDados.isOpen()){
            return false;
        }else{
            return true;
        }
    }
};

#endif // CONEXAO_H
