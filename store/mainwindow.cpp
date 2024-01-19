#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString login = ui->login->text();
   if (login != ""){
       hide();
       QFile fileOut("C:/Users/8gg7t/Desktop/store/cheque.txt");
       if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
           QTextStream Out(&fileOut);
           Out << login << "\n";
           fileOut.close();
       }
       market = new Market(this);
       market->show();
   }
}
