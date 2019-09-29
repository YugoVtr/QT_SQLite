#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <QString>
#include <QStringList>
#include "Usuario.h"
#include <queue>
#include <QtSql/QtSql>

namespace PBD {
    class Persistencia;
}

class Persistencia
{
public:
    Persistencia();
    ~Persistencia();
    void salvar(Usuario &obj);
    void excluir(Usuario &obj);
    std::queue<Usuario> *listar();
private:
    QSqlDatabase banco;
};

#endif // PERSISTENCIA_H
