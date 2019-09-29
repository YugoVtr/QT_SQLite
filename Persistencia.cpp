#include "Persistencia.h"

Persistencia::Persistencia()
{
    try
    {
        //Ao instanciar a persistencia inicia-se a conexão com o banco
        banco = QSqlDatabase::addDatabase("QSQLITE");
        banco.setDatabaseName("../usuarioLite/banco.db");

        if(!banco.open()) {
            throw QString(banco.lastError().text());
        }

    } catch (QString &erro) { throw QString(erro); }
}

Persistencia::~Persistencia()
{
    banco.close();
}

void Persistencia::salvar(Usuario &obj)
{
    try
    {
        //A classe QSqlQuery executa requisições ao SGBD
        QSqlQuery execQuery;
        execQuery.prepare("INSERT INTO Usuario(id,nome) VALUES (:id,:nome)");
        execQuery.bindValue(":id",obj.getId());
        execQuery.bindValue(":nome",obj.getNome());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

void Persistencia::excluir(Usuario &obj)
{
    try
    {
        QSqlQuery execQuery;
        execQuery.prepare("DELETE FROM Usuario WHERE id = :id");
        execQuery.bindValue(":id",obj.getId());

        if(!execQuery.exec())
        {
            throw QString(execQuery.lastError().text());
        }
    } catch (QString &erro) { throw QString(erro); }
}

std::queue<Usuario> *Persistencia::listar()
{
    try
    {
        QString query = "SELECT * FROM Usuario";

        QSqlQuery queryExec;
        if(!queryExec.exec(query))
        {
            throw QString(queryExec.lastError().text());
        }

        QSqlRecord rec = queryExec.record();

        std::queue<Usuario> *saida = new std::queue<Usuario>();

        while(queryExec.next())
        {
            qint64 id = queryExec.value(rec.indexOf("id")).toInt();
            QString nome = queryExec.value(rec.indexOf("nome")).toString();

            Usuario atual(id,nome);
            saida->push(atual);
        }

        return saida;

    } catch (QString &erro) { throw QString(erro); }
      catch (std::bad_alloc&) { throw QString("000 - Erro de alocação de memória"); }
}
