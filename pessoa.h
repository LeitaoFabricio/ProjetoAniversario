#ifndef PESSOA_H
#define PESSOA_H

#include <QString>
#include <QDate>
#include <QDateEdit>

class Pessoa
{
private:
  QString nome;
  QDate data;
  QString descricao;
  int idade;
public:
  Pessoa(); 
  QString getNome() const;
  QDate getData() const;
  QString getDescricaoPessoa() const;
  int getIdade() const;
  bool setNome(const QString &value);
  bool setData(const QDate &value);
  bool setDescricaoPessoa(const QString &value);
  void setIdade(const QDate &value);
  void setIdade(const QString &value);

};

#endif // PESSOA_H
