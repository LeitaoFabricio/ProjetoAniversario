#include "lista.h"

Lista::Lista()
{

}

void Lista::inserirPessoa(Pessoa p)
{
  minhalista.push_back(p);
}

void Lista::ordenarPorNome()
{
  std::sort(minhalista.begin(),minhalista.end(),[](Pessoa a, Pessoa b){
    return a.getNome()<b.getNome();
  });
}

int Lista::size()
{
  return minhalista.size();
}

Pessoa Lista::operator[](int indice)
{
  return minhalista[indice];
}


