#include "pessoa.h"

QString Pessoa::getNome() const
{
    return nome;
}

void Pessoa::setNome(const QString &value)
{
    if(value.size()>3)
        nome = value;
}

Pessoa::Pessoa()
{

}
