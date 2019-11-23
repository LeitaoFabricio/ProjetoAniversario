#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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

  void on_btOrdenacao_clicked();

private:
  Ui::MainWindow *ui;

  Lista minhalista;

  void inserirNaTabela(Pessoa p, int q_l);
};

#endif // MAINWINDOW_H
