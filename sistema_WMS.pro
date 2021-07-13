QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cadastro_de_clientes.cpp \
    cadastro_de_fornecedores.cpp \
    cadastro_de_produtos_no_estoque.cpp \
    cadastro_de_transportadoras.cpp \
    cadastro_estoque.cpp \
    cadastro_produtos.cpp \
    cadastro_usuarios.cpp \
    consulta_de_pedidos.cpp \
    entrada_produtos_estoque.cpp \
    janela_login.cpp \
    lancar_entrada_no_estoque.cpp \
    main.cpp \
    janela_principal.cpp \
    pedido_de_compra.cpp \
    separacao_de_pedidos.cpp

HEADERS += \
    cadastro_de_clientes.h \
    cadastro_de_fornecedores.h \
    cadastro_de_produtos_no_estoque.h \
    cadastro_de_transportadoras.h \
    cadastro_estoque.h \
    cadastro_produtos.h \
    cadastro_usuarios.h \
    conexao.h \
    consulta_de_pedidos.h \
    entrada_produtos_estoque.h \
    funcoes_globais.h \
    janela_login.h \
    janela_principal.h \
    lancar_entrada_no_estoque.h \
    pedido_de_compra.h \
    separacao_de_pedidos.h \
    variaveis_globais.h

FORMS += \
    cadastro_de_clientes.ui \
    cadastro_de_fornecedores.ui \
    cadastro_de_produtos_no_estoque.ui \
    cadastro_de_transportadoras.ui \
    cadastro_estoque.ui \
    cadastro_produtos.ui \
    cadastro_usuarios.ui \
    consulta_de_pedidos.ui \
    entrada_produtos_estoque.ui \
    janela_login.ui \
    janela_principal.ui \
    lancar_entrada_no_estoque.ui \
    pedido_de_compra.ui \
    separacao_de_pedidos.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
