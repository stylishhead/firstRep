#include "market.h"
#include "ui_market.h"


Market::Market(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Market)
{
    ui->setupUi(this);
    setProducts();
}

Market::~Market()
{
    delete ui;
}



void Market::on_pushButton_clicked()
{
    summary();
}

void Market::setProducts(){
    QFile fileIn("C:/Users/8gg7t/Desktop/store/products.txt");
    int j=0;
    int row=0;
    ui->table->setColumnCount(4);
    if(fileIn.open(QIODevice::ReadOnly)){//считывание с файла в таблицу
        while (!fileIn.atEnd()){
            row++;
            ui->table->setRowCount(row);
            QString block = fileIn.readLine();
            QString nameOfProduct = "";
            int i=0;
            while(block[i+1] != "-"){
                nameOfProduct+=block[i];
                i++;
            }
            i++;
            i++;
            QString count = "";
            while(block[i+1] != "|"){
                if(block[i]!=" "){
                    count+=block[i];
                }
                i++;
            }
            int quantityHave = count.toInt();
            i++;
            i++;
            count = "";
            while(block[i]!=block[block.length()]){
                if(block[i]!=" "){
                    count+=block[i];
                }
                i++;
            }
            int price = count.toInt();
            ui->table->setItem(j,0, new QTableWidgetItem(nameOfProduct));
            ui->table->setItem(j,1,new QTableWidgetItem(QString::number(quantityHave)));
            ui->table->setItem(j,2,new QTableWidgetItem(QString::number(price)));
            QSpinBox *qsb=new QSpinBox();
            qsb->setMaximum(quantityHave);
            ui->table->setCellWidget(j,3,qsb);
            j++;
        }
        fileIn.close();
        ui->table->setEditTriggers(0);
    }
    ui->table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
}

void Market::summary(){
    int summa = 0;
    QFile fileIn("C:/Users/8gg7t/Desktop/store/products.txt");
    QFile fileOut("C:/Users/8gg7t/Desktop/store/cheque.txt");
    if (fileIn.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Append)){
            QTextStream In(&fileIn);
            QTextStream Out(&fileOut);
            for(int i=0; i < ui->table->rowCount(); i++){
                QSpinBox *sp_1 = (QSpinBox *)ui->table->cellWidget(i,3);
                int choose = sp_1->value();
                if (choose!=0){
                    QString name = ui->table->item(i, 0)->text();
                    int quantity = ui->table->item(i, 1)->text().toInt();
                    int price = ui->table->item(i, 2)->text().toInt();
                    quantity = quantity - choose;
                    summa += price*choose;
                    In << name << " - " << quantity << " | " << price << "\n";
                    Out << name << " - " << choose << "\n";
                }
            }
            Out << "Total price " << summa;
        }
    }
    fileIn.close();
    fileOut.close();
    setProducts();
}


