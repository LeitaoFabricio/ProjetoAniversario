#include "modificar.h"
#include "ui_modificar.h"

Modificar::Modificar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modificar)
{
    ui->setupUi(this);

    ui->novo_nome->setEnabled(false);
    ui->nova_data->setEnabled(false);
    ui->nova_legenda->setEnabled(false);
}

Modificar::~Modificar()
{
    delete ui;
}

void Modificar::setAlterarNome(const QString &value)
{
    nome_alterado = value;
    emit nomeAlterado();
    close();
}

QString Modificar::getAlterarNome()
{
    return nome_alterado;
}



void Modificar::on_buttonBox_rejected()
{
    close();
}



void Modificar::on_escolha_modificar_tabela_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Excluir linha"){
        qDebug() << "Deve-se exlcuir";

        ui->novo_nome->setEnabled(false);
        ui->nova_data->setEnabled(false);
        ui->nova_legenda->setEnabled(false);
    }
    else if(arg1 == "Editar dados da pessoa"){
        qDebug() << "Habilitar-se-á a edição";

        ui->novo_nome->setEnabled(true);
        ui->nova_data->setEnabled(true);
        ui->nova_legenda->setEnabled(true);
    }
}

void Modificar::on_buttonBox_accepted()
{
    setAlterarNome(ui->novo_nome->text());
    QDate d(2000, 1, 1);
    ui->novo_nome->clear();
    ui->nova_data->QDateEdit::setDate(d);
    ui->nova_legenda->clear();
    ui->escolha_modificar_tabela->setCurrentIndex(0);

    qDebug() << getAlterarNome();
}
