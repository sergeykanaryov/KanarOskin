#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "form.h"
#include <QFile>
#include <QByteArray>
#include <QString>

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

void MainWindow::on_pushButton_4_clicked() // Помощь.
{
    QMessageBox::information(this, "Help", "To exit the game press the Quit."
                                           "\nTo get information about the results of players, press Results."
                                           "\nTo start the game, click Start a new game."
                                           "\nThe game is controlled by the mouse pointer. Click on the picture to move it to the empty space."
                                           "\nPress Enter to return to the menu...");
}


void MainWindow::on_pushButton_2_clicked()
{
    QFile file("file.txt");
        QByteArray data;
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, "Help", "Cant open the file");
            return;
        }
        data = file.readAll();
        QMessageBox::information(this, "Results", data);
}
