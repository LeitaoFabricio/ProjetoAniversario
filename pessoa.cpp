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

int Pessoa::getIdade() const
{
  return idade;
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
  QDate data_atual = data_atual.currentDate();
  int ano = value.year();
  int mes = value.month();
  int dia = value.day();
  int ano_atual = data_atual.year();
  int mes_atual = data_atual.month();
  int dia_atual = data_atual.day();

  if(ano_atual >= ano){//completar
      data = value;
      return true;
  } else{
    return false;
  }
}

bool Pessoa::setDescricaoPessoa(const QString &value)
{
  descricao = value;
  return true;
}

void Pessoa::setIdade(const QDate &value)
{
  QDate data_atual = data_atual.currentDate();

  if(data_atual.year() > value.year()){

    if(data_atual.month() == value.month() and data_atual.day() >= value.day()
       or data_atual.month() > value.month() and data_atual.day() < value.day()){
      idade = data_atual.year() - value.year();
    }else{
      idade = data_atual.year() - value.year() - 1;//pode-se calcular o tempo até o aniversário
    }

  } else{
    idade = 0;//completar, informando os meses de idade
  }
}

Pessoa::Pessoa()
{

}
