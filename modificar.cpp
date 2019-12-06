#include "modificar.h"
#include "ui_modificar.h"

Modificar::Modificar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modificar)
{
    ui->setupUi(this);

}

Modificar::~Modificar()
{
    delete ui;
}


void Modificar::on_escolha_modificar_tabela_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Excluir linha"){
        qDebug() << "Deve-se exlcuir";
    }
    else if(arg1 == "Editar dados da pessoa"){
        qDebug() << "Habilitar-se-á a edição";
    }
}

void Modificar::on_buttonBox_accepted()
{

}
