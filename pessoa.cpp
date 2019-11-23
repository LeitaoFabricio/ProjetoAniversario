#include "pessoa.h"

QString Pessoa::getNome() const
{
  return nome;
}

bool Pessoa::setNome(const QString &value)
{
  if(value.size()>=3){
      nome = value;
      return true;
   }else
      return false;
}

Pessoa::Pessoa()
{

}
