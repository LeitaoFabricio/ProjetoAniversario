#include "pessoa.h"

QString Pessoa::getNome() const
{
  return nome;
}

QDate Pessoa::getData() const
{
  return data;
}

QString Pessoa::getDescricaoPessoa() const
{
  return descricao;
}

bool Pessoa::setNome(const QString &value)
{
  if(value.size()>=3){
      nome = value;
      return true;
   }else
    return false;
}

bool Pessoa::setData(const QDate &value)
{
  data = value;
  return true;
}

bool Pessoa::setDescricaoPessoa(const QString &value)
{
  descricao = value;
  return true;
}

Pessoa::Pessoa()
{

}
