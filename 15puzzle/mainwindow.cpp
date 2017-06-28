#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
//#include "form.h"

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
void MainWindow::on_pushButton_clicked() // Старт.
{
    Form *f = new Form();
    f->show();
    this->close();
}

//void MainWindow::on_pushButton_2_clicked() // Помощи.
//{
  //  QMessageBox::information(this, "Help", "\nPress Enter to return to the menu..."//  );
//}
