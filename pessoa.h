#ifndef PESSOA_H
#define PESSOA_H

#include <QString>
#include <QDate>

class Pessoa
{
private:
  QString nome;
  QDate data;
public:
  Pessoa(); 
  QString getNome() const;
  QDate getData() const;
  bool setNome(const QString &value);
  bool setData(const QDate &value);

};

#endif // PESSOA_H
