#ifndef PESSOA_H
#define PESSOA_H

#include <QString>

class Pessoa
{
private:
  QString nome;
  //e data
public:
  Pessoa();
  QString getNome() const;
  void setNome(const QString &value);

};

#endif // PESSOA_H
