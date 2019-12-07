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

  if(value <= data_atual){//completar
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
    int idade_em_dias = 0;

    QDate data_atual = data_atual.currentDate();

    idade_em_dias = value.daysTo(data_atual);

    idade = idade_em_dias/365;




      /*
      if(data_atual.year() > value.year()){

        if((data_atual.month() == value.month() && data_atual.day() >= value.day()) || (data_atual.month() > value.month() && data_atual.day() < value.day())){
          idade = data_atual.year() - value.year();
        }else{
          idade = data_atual.year() - value.year() - 1;//pode-se calcular o tempo até o aniversário
        }

      } else{
        idade = 0;//completar, informando os meses de idade
      }*/
}

void Pessoa::setIdade(const QString &value)
{
  idade = value.toInt();
}

Pessoa::Pessoa()
{

}
