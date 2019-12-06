#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //Impede a edição direta da tabela pelo usuário
  ui->tabelaAniversarios->setEditTriggers(QAbstractItemView::NoEditTriggers);

  connect(&janela_modificar, SIGNAL(nomeAlterado()), this, SLOT(atualizarNome()));
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
    QDate data = ui->inputData->date();
    QString descricao = ui->descricaoPessoaText->toPlainText();

    bool testa_nome = pessoa.setNome(nome);
    bool testa_data = pessoa.setData(data);
    pessoa.setDescricaoPessoa(descricao);
    pessoa.setIdade(data);

    if(testa_nome == true && testa_data == true){

      limparCamposCadastro();
      //Inserindo a pessoa na lista
      bool inserido_na_lista = minhalista.inserirPessoa(pessoa);//dúvida
      //Inserindo dados na tabela
      if(inserido_na_lista == true){
        qDebug() << "inserido no vetor";
        qtde_linhas = ui->tabelaAniversarios->rowCount();
        //Nova linha na tabela
        ui->tabelaAniversarios->insertRow(qtde_linhas);
        inserirNaTabela(pessoa, qtde_linhas);
       }
    }else{
        //if(testa_data == true && testa_nome == false)
            //QMessageBox::warning(this,"Nome inválido","Digite um nome válido.");
        //else if(testa_data == false && testa_nome == true)
            //QMessageBox::warning(this,"Data inválida","Digite uma data válida.");
        //else if(testa_data == false && testa_nome == false)
            QMessageBox::warning(this,"Dados inválidos","Insira dados válidos.");
    }
    habilitarOrdenacao();
    atualizarEstatisticas();
}
//---------------------------------------------------------------//
QString MainWindow::prepararData(QDate d1)
{
/*
  QString d = QString::number(d1.day());
  QString m = QString::number(d1.month());
  QString a = QString::number(d1.year());

  return d+"/"+m+"/"+a;
*/
  QString data = d1.toString(Qt::RFC2822Date);
  return data;
}
//----------------------------------------------------------------//
void MainWindow::inserirNaTabela(Pessoa p, int q_l)
{
        QString data1 = prepararData(p.getData());
        ui->tabelaAniversarios->setItem(q_l,0, new QTableWidgetItem(p.getNome()));
        ui->tabelaAniversarios->setItem(q_l,1, new QTableWidgetItem(data1));
        ui->tabelaAniversarios->setItem(q_l,2, new QTableWidgetItem(p.getDescricaoPessoa()));
        ui->tabelaAniversarios->setItem(q_l,3, new QTableWidgetItem(QString::number(p.getIdade())));
}
//---------------------------------------------------------------------//
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
bool MainWindow::limparOrdenacao(int a1, int a2)
{
  if(a1 == 0 && a2 == 1){
    ui->ordenacao->setCurrentIndex(0);
    return true;
  }else{
    return false;
  }
}
//---------------------------------------------------------------//
bool MainWindow::limparOrdenacao()
{
  ui->ordenacao->setCurrentIndex(0);
  return true;
}
//---------------------------------------------------------------//
void MainWindow::atualizarNome()//Aqui dá problema
{
    Pessoa pessoa;

    bool testa_nome = pessoa.setNome(janela_modificar.getAlterarNome());

    if(testa_nome == 1){
        minhalista.inserirPessoa(pessoa);

    }
}
//---------------------------------------------------------------//
void MainWindow::limparCamposCadastro()
{
  QDate d(2000, 1, 1);
  ui->inputNome->clear();
  ui->inputData->QDateEdit::setDate(d);
  ui->descricaoPessoaText->clear();
}
//---------------------------------------------------------------//
void MainWindow::atualizarEstatisticas()
{
  ui->pmv->setText(minhalista.getMaiorIdadePessoa());
  ui->pmn->setText(minhalista.getMenorIdadePessoa());
  ui->maiori->setText(QString::number(minhalista.getMaiorIdade()));
  ui->menori->setText(QString::number(minhalista.getMenorIdade()));
}
//---------------------------------------------------------------//
void MainWindow::on_ordenacao_currentIndexChanged(const QString &arg1)
{
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
          minhalista.ordenarPorData();
          ui->tabelaAniversarios->clearContents();
          //Inserindo vetor ordenado na tabela
          for(int i=0; i<minhalista.size();i++){
            inserirNaTabela(minhalista[i],i);
          }//Ideia: uma função com essa finalidade
        }
    }
}
//---------------------------------------------------------------------//
void MainWindow::on_inputNome_cursorPositionChanged(int arg1, int arg2)
{
  limparOrdenacao(arg1, arg2);
}
//---------------------------------------------------------------------//
void MainWindow::on_inputData_userDateChanged(const QDate &date)
{
    limparOrdenacao();
}
//---------------------------------------------------------------------//
void MainWindow::on_actionSalvar_triggered()
{
  QString filename;
  filename = QFileDialog::getSaveFileName(this,"Salvar Arquivo","","*.csv");
  minhalista.salvarDados(filename);
}
//--------------------------------------------------------------------//
void MainWindow::on_actionCarregar_triggered()
{
  QString filename;
  filename = QFileDialog::getOpenFileName(this, "Abrir Arquivo","","*.csv");
  minhalista.carregarDados(filename);

  if(minhalista.inserirPessoa() == true){
    for(int i=0;i<minhalista.size();i++){
          ui->tabelaAniversarios->insertRow(i);
          inserirNaTabela(minhalista[i],i);
    }
  }
  habilitarOrdenacao();
  atualizarEstatisticas();
}
//---------------------------------------------------------------------//
void MainWindow::on_inputNome_returnPressed()
{
    ui->inputData->setFocus();
}
//---------------------------------------------------------------------//
void MainWindow::on_bt_editarTabela_clicked()
{
    QMessageBox::StandardButton resposta = QMessageBox::question(this,"Modificar tabela","Deseja mexer na tabela?");
    if(resposta == QMessageBox::Yes){
        janela_modificar.show();
    }
}

