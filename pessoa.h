#ifndef PESSOA_H
#define PESSOA_H

#include <QString>
#include <QDate>

class Pessoa
{
private:
  QString nome;
  QDate data;
  QString descricao;
public:
  Pessoa(); 
  QString getNome() const;
  QDate getData() const;
  QString getDescricaoPessoa() const;
  bool setNome(const QString &value);
  bool setData(const QDate &value);
  bool setDescricaoPessoa(const QString &value);

};

#endif // PESSOA_H
