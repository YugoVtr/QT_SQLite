#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

namespace PBD {
    class Usuario;
}

class Usuario
{
private:
    qint64 id;
    QString nome;

public:
    Usuario();
    Usuario(qint64 cpf, QString nome);
    Usuario(const Usuario &usuario);
    QString getNome() const;
    void setNome(const QString &value);
    qint64 getId() const;
    void setId(const qint64 &value);
};

#endif // USUARIO_H
