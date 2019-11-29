#ifndef LISTA_H
#define LISTA_H

#include <QVector>
#include <algorithm>

#include "pessoa.h"

class Lista
{
private:
  QVector <Pessoa> minhalista;
public:
  Lista();
  void inserirPessoa(Pessoa p);
  void ordenarPorNome();
  void ordenarPorData();
  int size();
  Pessoa operator[](int indice);
};

#endif // LISTA_H
