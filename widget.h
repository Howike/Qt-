#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<QStack>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    int isTwo(QString temp);    //是否二进制

    void toComplement(QString &temp); //转换为补码

    void toSameSize(QString &temp1,QString &temp2); //补位

    void add(QString &temp1,QString &temp2);     //二进制加法

    void toOpposite(QString &temp);  //带符号位取反

    void toUOpposite(QString &temp);    //取反

    void toDecimal(QString &str);   //十

    void toPDecimal(QString &str);

    void toBinary(QString &str);    //2

    void toPBinary(QString &str);

    void toB(int d);

    void toPB(float d);

    void on_pushButtonLogin_clicked();

    void on_pushButtonPage1_Non_clicked();

    void on_pushButtonPage0_1_clicked();

    void on_pushButtonPage0_2_clicked();

    void on_pushButtonPage0_3_clicked();

    void on_pushButtonPage0_4_clicked();

    void on_pushButtonPage1_Create_clicked();

    void on_pushButtonPage1_Mul_clicked();

    void on_pushButtonPage1_Exc_clicked();

    void on_pushButtonPage1_Input_clicked();

    void on_pushButtonPage1_return_clicked();

    void on_pushButtonPage2_Input_clicked();

    void on_pushButtonPage2_Return_clicked();

    void on_pushButtonPage2_Plus_clicked();

    void on_pushButtonPage2_Del_clicked();

    void on_pushButtonPage3_Input_clicked();

    void on_pushButtonPage3_Return_clicked();

    void on_pushButtonPage3_Mul_clicked();

    void on_pushButtonPage4_Input_clicked();

    void on_pushButtonPage4_Return_clicked();

    void on_pushButtonPage4_Plus_clicked();

    void on_pushButtonPage4_Del_clicked();

private:
    Ui::Widget *ui;

    QString::iterator strIter;  // 迭代器
    QStack<QChar> myStack1;
    QStack<QChar> myStack2;
    QStack<QString> myStack3;
    QStack<int> myStack4;
};

#endif // WIDGET_H
