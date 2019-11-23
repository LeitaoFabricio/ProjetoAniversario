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

    bool testa_nome = pessoa.setNome(nome);
    if(testa_nome == true){
      ui->inputNome->clear();

      qtde_linhas = ui->tabelaAniversarios->rowCount();
      //Nova linha na tabela
      ui->tabelaAniversarios->insertRow(qtde_linhas);
      //Inserindo dados na tabela
      inserirNaTabela(pessoa, qtde_linhas);
      //Inserindo a pessoa na lista
      minhalista.inserirPessoa(pessoa);//dúvida
    }
    habilitarOrdenacao();
}
//---------------------------------------------------------------//
void MainWindow::inserirNaTabela(Pessoa p, int q_l)
{
  ui->tabelaAniversarios->setItem(q_l,0, new QTableWidgetItem(p.getNome()));
}

bool MainWindow::habilitarOrdenacao()
{
  if(minhalista.size() >= 2){
    ui->ordenacao->setEnabled(true);//habilitar (true)/inabilitar (false) um input widget
    return true;
  }else{
      ui->ordenacao->setEnabled(false);
      return false;
  }
}
//---------------------------------------------------------------//
void MainWindow::on_ordenacao_currentIndexChanged(const QString &arg1)
{//Pode ser aperfeiçoado?
    //qDebug() << arg1;//A possibilidade de usar o ComboBox para selecionar o critério de ordenação
    if(ui->ordenacao->currentText() == "Ordenar por nome")
    {
        minhalista.ordenarPorNome();
        ui->tabelaAniversarios->clearContents();
        //Inserindo vetor ordenado na tabela
        for(int i=0; i<minhalista.size();i++){
            inserirNaTabela(minhalista[i],i);
        }//Ideia: uma função com essa finalidade

        ui->ordenacao->objectName().isEmpty();
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
