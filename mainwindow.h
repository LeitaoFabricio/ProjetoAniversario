#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QDateEdit>

#include "pessoa.h"
#include "lista.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void on_btConfirmar_clicked();

  void on_ordenacao_currentIndexChanged(const QString &arg1);

  void on_inputNome_cursorPositionChanged(int arg1, int arg2);

  void on_inputData_userDateChanged(const QDate &date);

private:
  Ui::MainWindow *ui;

  Lista minhalista;

  void inserirNaTabela(Pessoa p, int q_l);

  void mensagemDeErro();

  bool habilitarOrdenacao();

  bool limparOrdenacao(int a1, int a2);

};

#endif // MAINWINDOW_H
