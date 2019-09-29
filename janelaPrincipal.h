#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "Persistencia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Salvar_clicked();
    void listagem();
    void excluirUsuario(QString &id);
    void limparGrid();

    void on_tableWidget_Listagem_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    Persistencia *persistencia;
};
#endif // MAINWINDOW_H
