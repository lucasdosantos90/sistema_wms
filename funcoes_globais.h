#ifndef FUNCOES_GLOBAIS_H
#define FUNCOES_GLOBAIS_H

#include <QString>
#include <QDesktopWidget>
#include <QApplication>
#include <janela_principal.h>

class funcoes_globais{
public:/* ---------------JANELA AO CENTRO----------------------
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;
    QRect rec = desktop->screenGeometry();
    screenWidth = rec.width(); // get width of screen
    screenHeight = rec.height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    // move window to desired coordinates
    move ( x, y );*/


//------------------------------------------------------------------

    //      JANELAS SEM MAXIMIZAR
    //    Qt::WindowFlags flags = windowFlags();
    //    flags |= Qt::CustomizeWindowHint;
    //    flags &= ~Qt::WindowContextHelpButtonHint;
    //    flags &= ~Qt::WindowSystemMenuHint;
    //    flags &= ~Qt::WindowMinMaxButtonsHint;
    //    //flags &= ~Qt::WindowCloseButtonHint;
    //    setWindowFlags(flags);
};

#endif // FUNCOES_GLOBAIS_H
