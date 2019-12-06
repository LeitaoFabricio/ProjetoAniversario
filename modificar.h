#ifndef MODIFICAR_H
#define MODIFICAR_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QDate>


namespace Ui {
class Modificar;
}

class Modificar : public QDialog
{
    Q_OBJECT

public:
    explicit Modificar(QWidget *parent = 0);
    ~Modificar();
    void setAlterarNome(const QString &value);
    QString getAlterarNome();

private slots:

    void on_escolha_modificar_tabela_currentTextChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::Modificar *ui;

signals:
    void respostaOpcao();

};

#endif // MODIFICAR_H
