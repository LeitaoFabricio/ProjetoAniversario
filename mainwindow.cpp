#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  //Impede a edição direta da tabela pelo usuário
  ui->tabelaAniversarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
  habilitarOrdenacao();

  connect(&janela_modificar, SIGNAL(respostaOpcao()), this, SLOT(atualizarNome()));

  //connect(ui->btEditar, SIGNAL(clicked(clicado1)), this, SLOT(slotBotaoEditar(Pessoa p)));
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
      } else{
          dadosRepetidos(pessoa);
      }
      habilitarOrdenacao();
      atualizarEstatisticas();
    }else{
      invalidosDataNome(testa_data,testa_nome);
    }
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
//--------------------------------------------------------------//
void MainWindow::dadosRepetidos(Pessoa p)
{
    QMessageBox::warning(this,"Dados repetidos", p.getNome()+", "+p.getData().toString()+", já consta na tabela.\nInsira dados que ainda não constem na tabela.");
}

void MainWindow::invalidosDataNome(bool td, bool tn)
{
    if(td == true && tn == false)
        QMessageBox::warning(this,"Nome inválido","Digite um nome válido.");
    else if(td == false && tn == true)
        QMessageBox::warning(this,"Data inválida","Digite uma data válida.");
    else if(td == false && tn == false)
        QMessageBox::warning(this,"Dados inválidos","Insira dados válidos.");
}
//---------------------------------------------------------------//
void MainWindow::atualizarNome()//Aqui dá problema
{
    qDebug() << janela_modificar.getAlterarNome();

    if(janela_modificar.getAlterarNome() == "Excluir linha"){
        minhalista.deletarPessoa(row1);

        QMessageBox::information(this,"Edição realizada com sucesso!","Pessoa removida.");

        ui->tabelaAniversarios->removeRow(row1);
        ui->tabelaAniversarios->clearContents();
        for(int i=0; i<minhalista.size();i++){
          inserirNaTabela(minhalista[i],i);
        }

        atualizarEstatisticas();
    }
    else if(janela_modificar.getAlterarNome() == "Editar dados da pessoa"){

            ui->inputNome->setText(minhalista[row1].getNome());
            ui->label_6->setText("Insira um novo nome");
            ui->inputData->setDate(minhalista[row1].getData());
            ui->label_7->setText("Insira uma nova data");
            ui->descricaoPessoaText->setText(minhalista[row1].getDescricaoPessoa());
            ui->label_10->setText("Insira uma nova legenda");

            ui->btConfirmar->setEnabled(false);
            ui->btEditar->setEnabled(true);

            on_btEditar_clicked(clicado1);//gambiarra

    }
    janela_modificar.close();
}
//---------------------------------------------------------------//
void MainWindow::limparCamposCadastro()
{
  QDate d(2000, 1, 1);
  ui->inputNome->clear();
  ui->inputData->QDateEdit::setDate(d);
  ui->descricaoPessoaText->clear();

  ui->label_6->clear();
  ui->label_7->clear();
  ui->label_10->clear();
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
    if(minhalista.size() >= 1){
        QString filename;
        filename = QFileDialog::getSaveFileName(this,"Salvar Arquivo","","*.csv");
        minhalista.salvarDados(filename);
    } else {
        QMessageBox::warning(this,"Tabela vazia","Nenhuma informação disponível para ser salva.");
    }
}
//--------------------------------------------------------------------//
void MainWindow::on_actionCarregar_triggered()
{
  //if(minhalista.size() >= 1){
    //minhalista.apagaTudoDaLista();
    //ui->tabelaAniversarios->clearContents();
  //}
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
void MainWindow::on_tabelaAniversarios_cellDoubleClicked(int row, int column)
{
    ui->tabelaAniversarios->selectRow(row);
    janela_modificar.show();

    row1 = row;
}
//----------------------------------------------------------------------------------//
void MainWindow::on_btEditar_clicked(bool checked)
{
    clicado1 = checked;
    if(clicado1 == false){

        bool testa_nome = p_alterada.setNome(ui->inputNome->text());
        bool testa_data = p_alterada.setData(ui->inputData->date());
        p_alterada.setDescricaoPessoa(ui->descricaoPessoaText->toPlainText());
        p_alterada.setIdade(ui->inputData->date());

        if(testa_nome == true && testa_data == true){
            limparCamposCadastro();

            bool substituindo_pessoa = minhalista.substituirPessoa(row1, p_alterada);
            qDebug() << "Pessoa substituída";

            if(substituindo_pessoa == true){
                ui->tabelaAniversarios->clearContents();
                for(int i=0; i<minhalista.size();i++){
                  inserirNaTabela(minhalista[i],i);
                }
            } else{
                dadosRepetidos(p_alterada);
            }
            atualizarEstatisticas();
            ui->btConfirmar->setEnabled(true);
            ui->btEditar->setEnabled(false);
            clicado1 = true;

        } else{
            invalidosDataNome(testa_data,testa_nome);
        }
    }
}
