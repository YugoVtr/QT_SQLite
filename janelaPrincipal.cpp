#include "janelaPrincipal.h"
#include "ui_janelaPrincipal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Id->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->lineEdit_Id));
    try{
        //Instancia o controle
        persistencia = new Persistencia;
        this->listagem();
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

MainWindow::~MainWindow()
{
    delete persistencia;
    delete ui;
}


void MainWindow::on_pushButton_Salvar_clicked()
{
    try
    {
        //Monta o objeto Usuario com os Dados da Window
        Usuario novo(ui->lineEdit_Id->text().toInt(), ui->lineEdit_Nome->text());

        this->persistencia->salvar(novo);
        QMessageBox::about(this,"Salvo","Salvo com sucesso");

        this->listagem();
    } catch (QString &erro) { QMessageBox::information(this,"ERRO",erro);}

}

void MainWindow::listagem()
{
    try{
        this->limparGrid();
        //Exibe a listagem dos Usuarios na Grid
        std::queue<Usuario> *fila = persistencia->listar();
        while(!fila->empty())
        {
            Usuario atual = fila->front();

            // Setando itens na grid
            ui->tableWidget_Listagem->setRowCount(ui->tableWidget_Listagem->rowCount()+1);
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,0,new QTableWidgetItem( QString::number(atual.getId()) ));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,1,new QTableWidgetItem(atual.getNome()));
            ui->tableWidget_Listagem->setItem(
                        ui->tableWidget_Listagem->rowCount()-1,2,new QTableWidgetItem("Remover"));
            fila->pop();
        }
        ui->tableWidget_Listagem->resizeColumnsToContents();
        ui->tableWidget_Listagem->setColumnWidth(1, 300);
        ui->tableWidget_Listagem->setColumnWidth(2, 50);
    } catch(QString &erro) {
        throw QString(erro);
    }
}

void MainWindow::excluirUsuario(QString &id)
{
    //Excluir um Usuario da base de dados
    Usuario excluir;
    excluir.setId(id.toInt());
    this->persistencia->excluir(excluir);
}

void MainWindow::on_tableWidget_Listagem_cellDoubleClicked(int row, int column)
{
    if(column == ui->tableWidget_Listagem->columnCount()-1)
    {
        QString id = ui->tableWidget_Listagem->item(row,0)->text();
        if(QMessageBox::question(this,"Excluir","Deseja excluir ?") == QMessageBox::Yes)
        {
            this->excluirUsuario(id);
            this->listagem();
        }
    }
}

void MainWindow::limparGrid()
{
    //Limpa a gride, deletando os intens criados
    for(int i=0;i<ui->tableWidget_Listagem->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget_Listagem->columnCount();j++)
        {
            if(ui->tableWidget_Listagem->itemAt(i,j))
                delete ui->tableWidget_Listagem->itemAt(i,j);
        }
    }
    ui->tableWidget_Listagem->setRowCount(0);
}
