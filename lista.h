#ifndef LISTA_H
#define LISTA_H

#include <QVector>
#include <algorithm>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include<string>
#include "pessoa.h"

class Lista
{
private:
  QVector <Pessoa> minhalista;
  bool x;
public:
  Lista();
  int getMaiorIdade();
  int getMenorIdade();
  QString getMaiorIdadePessoa();
  QString getMenorIdadePessoa();
  bool inserirPessoa(Pessoa p);
  bool inserirPessoa();
  void ordenarPorNome();
  void ordenarPorData();
  int size();
  Pessoa operator[](int indice);
  void salvarDados(QString file);
  void carregarDados(QString file);
};

bool compararPorIdade(Pessoa a, Pessoa b);

#endif // LISTA_H
