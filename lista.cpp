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

void Lista::ordenarPorData()
{
  std::sort(minhalista.begin(),minhalista.end(),[](Pessoa a, Pessoa b){
    if(a.getData().month() == b.getData().month())
      return a.getData().day()<b.getData().day();
    else
      return a.getData().month()<b.getData().month();
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

void Lista::salvarDados(QString file)
{
  QFile arquivo(file);
  QString linha;

  arquivo.open(QIODevice::WriteOnly);

  for(auto a: minhalista){
     linha = a.getNome() + "," + a.getData().toString() + "," + a.getDescricaoPessoa() + "," + QString::number(a.getIdade()) + "\n";
     arquivo.write(linha.toLocal8Bit());
  }
  arquivo.close();
}


