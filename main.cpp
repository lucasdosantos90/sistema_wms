#include "janela_principal.h"
#include "janela_login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    janela_login login;
    login.exec();

    janela_principal w;
    w.show();
    return a.exec();
}
