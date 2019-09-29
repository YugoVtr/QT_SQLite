#include "Usuario.h"

QString Usuario::getNome() const
{
    return nome;
}

void Usuario::setNome(const QString &value)
{
    nome = value;
}

qint64 Usuario::getId() const
{
    return id;
}

void Usuario::setId(const qint64 &value)
{
    id = value;
}

Usuario::Usuario():id(0), nome("")
{

}
Usuario::Usuario(qint64 id, QString nome):
    id(id), nome(nome)
{

}
Usuario::Usuario(const Usuario &usuario):
    id(usuario.id), nome(usuario.nome)
{

}
