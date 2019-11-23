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
    QDateEdit data;
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
    }else{
      mensagemDeErro();
    }
    habilitarOrdenacao();
}
//---------------------------------------------------------------//
void MainWindow::inserirNaTabela(Pessoa p, int q_l)
{
  ui->tabelaAniversarios->setItem(q_l,0, new QTableWidgetItem(p.getNome()));
}

void MainWindow::mensagemDeErro()
{
  QMessageBox::critical(this,"Aviso de erro","O nome inserido é inválido.");
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

bool MainWindow::limparOrdenacao(int a1, int a2)
{
  if(a1 == 0 && a2 == 1){
    ui->ordenacao->setCurrentIndex(0);
    return true;
  }else
    return false;
}


//---------------------------------------------------------------//
void MainWindow::on_ordenacao_currentIndexChanged(const QString &arg1)
{//Pode ser aperfeiçoado?
    //qDebug() << arg1;//A possibilidade de usar o ComboBox para selecionar o critério de ordenação
    if(arg1 == "Ordenar por nome")
    {
        minhalista.ordenarPorNome();
        ui->tabelaAniversarios->clearContents();
        //Inserindo vetor ordenado na tabela
        for(int i=0; i<minhalista.size();i++){
            inserirNaTabela(minhalista[i],i);
        }//Ideia: uma função com essa finalidade
    }else{
        if(arg1 == "Ordenar por data")
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


void MainWindow::on_inputNome_cursorPositionChanged(int arg1, int arg2)
{
  limparOrdenacao(arg1, arg2);
}

void MainWindow::on_inputData_userDateChanged(const QDate &date)
{

}
