#ifndef LISTA_H
#define LISTA_H

#include <QVector>
#include <algorithm>
#include <QFile>
#include <QStringList>
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
  void salvarDados(QString file);
  void carregarDados(QString file);
};

#endif // LISTA_H
