#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}
//----------------------------------------------------------------//
void MainWindow::on_btConfirmar_clicked()
{
    Pessoa pessoa;
    int qtde_linhas;

    QString nome = ui->inputNome->text();

    pessoa.setNome(nome);

    ui->inputNome->clear();


    qtde_linhas = ui->tabelaAniversarios->rowCount();
    //Nova linha na tabela
    ui->tabelaAniversarios->insertRow(qtde_linhas);
    //Inserindo dados na tabela
    inserirNaTabela(pessoa, qtde_linhas);
    //Inserindo a pessoa na lista
    minhalista.inserirPessoa(pessoa);//dúvida

}
//---------------------------------------------------------------//
void MainWindow::inserirNaTabela(Pessoa p, int q_l)
{
  ui->tabelaAniversarios->setItem(q_l,0, new QTableWidgetItem(p.getNome()));
}
//---------------------------------------------------------------//
void MainWindow::on_btOrdenacao_clicked()
{
  if(ui->ordenacao->currentText() == "Ordenar por nome")
  {
      minhalista.ordenarPorNome();
      ui->tabelaAniversarios->clearContents();
      //Inserindo vetor ordenado na tabela
      for(int i=0; i<minhalista.size();i++){
          inserirNaTabela(minhalista[i],i);
      }//Ideia: uma função com essa finalidade
  }else{
      if(ui->ordenacao->currentText() == "Ordenar por data")
      {
        //minhalista.ordenarPorData();
        //ui->tabelaAniversarios->clearContents();
        //Inserindo vetor ordenado na tabela
        for(int i=0; i<minhalista.size();i++){
          inserirNaTabela(minhalista[i],i);
        }//Ideia: uma função com essa finalidade
      }
  }
}
