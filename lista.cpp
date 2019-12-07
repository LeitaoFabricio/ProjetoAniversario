#include "lista.h"

Lista::Lista()
{

}

int Lista::getMaiorIdade()
{
    Pessoa *p = std::max_element(minhalista.begin(),minhalista.end(),compararPorIdade);
    return p->getIdade();
}

int Lista::getMenorIdade()
{
    Pessoa *p = std::min_element(minhalista.begin(),minhalista.end(),compararPorIdade);
    return p->getIdade();
}

QString Lista::getMaiorIdadePessoa()
{
    Pessoa *p = std::max_element(minhalista.begin(),minhalista.end(),compararPorIdade);
    return p->getNome();
}

QString Lista::getMenorIdadePessoa()
{
    Pessoa *p = std::min_element(minhalista.begin(),minhalista.end(),compararPorIdade);
    return p->getNome();
}


bool Lista::inserirPessoa(Pessoa p)
{
  if (minhalista.size() == 0){
    minhalista.push_back(p);
    x = true;
    qDebug() << QString::number(minhalista.size()) + ", posição " + QString::number(minhalista.size()-1);
    return true;
  }
  if(minhalista.size() != 0){
    for(int i = 0;i < minhalista.size();i++){
      //std:: string w1 = p.getNome().toStdString(), w2 = minhalista[i].getNome().toStdString();
      //if(w1.std::string::find(w2) != -1 && p.getData() == minhalista[i].getData()){ //usar método find para testar o nome
      if((p.getNome() == minhalista[i].getNome() || p.getNome()+" " == minhalista[i].getNome() || p.getNome() == minhalista[i].getNome()+" " || p.getNome()+" " == minhalista[i].getNome()+" ") && p.getData() == minhalista[i].getData()){
          x = false;
          qDebug() << "Repetido";
          return false;
      }
    }
    minhalista.push_back(p);
    x = true;
    qDebug() << QString::number(minhalista.size()) + ", posição " + QString::number(minhalista.size()-1);
    return true;
    }
}

bool Lista::inserirPessoa()
{
  if(x == true)
    return true;
  else
    return false;
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

void Lista::carregarDados(QString file)
{
  QFile arquivo(file);
  arquivo.open(QIODevice::ReadOnly);

  QString linha;
  QStringList dados;

  while(!arquivo.atEnd()){
    Pessoa temp;
    QDate temp1;
    linha = arquivo.readLine();
    dados = linha.split(",");
    temp.setNome(dados[0]);
    temp.setData(temp1.fromString(dados[1]));
    temp.setDescricaoPessoa(dados[2]);
    temp.setIdade(dados[3]);

    inserirPessoa(temp);
    inserirPessoa();

  }
  arquivo.close();
}

void Lista::deletarPessoa(const int &linha)
{
    minhalista.remove(linha);
}

bool Lista::substituirPessoa(const int &linha, Pessoa p)
{
    if(inserirPessoa(p) == true){
        minhalista.replace(linha, p);
        return true;
    } else{
        return false;
    }
}

//bool Lista::apagaTudoDaLista()
//{
  //  minhalista.clear();
//}

bool compararPorIdade(Pessoa a, Pessoa b)
{
    return a.getIdade()<b.getIdade();
}
