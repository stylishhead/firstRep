#ifndef MARKET_H
#define MARKET_H


#include <QDialog>
#include <QFile>
#include <QByteArray>
#include <QSpinBox>
#include <QTextStream>
#include <QStandardItemModel>
#include <QListWidget>

namespace Ui {
class Market;
}

class Market : public QDialog
{
    Q_OBJECT

public:
    explicit Market(QWidget *parent = nullptr);
    ~Market();

private slots:
    void setProducts();
    void on_pushButton_clicked();
    void summary();
private:
    Ui::Market *ui;
};

#endif // MARKET_H
