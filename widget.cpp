#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include <QChar>
#include<QDebug>
#define cout qDebug() << "[" <<__FILE__<< ":" <<__LINE__<< "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化
    ui->pushButtonPage0_1->setEnabled(false);
    ui->pushButtonPage0_2->setEnabled(false);
    ui->pushButtonPage0_3->setEnabled(false);
    ui->pushButtonPage0_4->setEnabled(false);
    ui->pushButtonPage1_Exc->setEnabled(false);
    ui->pushButtonPage1_Mul->setEnabled(false);
    ui->pushButtonPage1_Non->setEnabled(false);
    ui->pushButtonPage1_Create->setEnabled(false);
    ui->pushButtonPage2_Del->setEnabled(false);
    ui->pushButtonPage2_Plus->setEnabled(false);
    ui->pushButtonPage3_Mul->setEnabled(false);
    ui->pushButtonPage4_Plus->setEnabled(false);
    ui->pushButtonPage4_Del->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);

}

Widget::~Widget()
{
    delete ui;
}

int Widget::isTwo(QString temp)    //是否为二进制数
{
    for(int i=0;i<temp.length();i++)
    {
        if(temp[i] =="1"||temp[i] =="0")
        {

        }
        else
        {
            QMessageBox::warning(this,"错误","请输入二进制数！",QMessageBox::Ok,QMessageBox::NoButton);
            return 0;
        }


    }
    return 1;
}

//转换补码
void Widget::toComplement(QString &temp)
{
    int num;
    QString temp3="1";
    for(int i = 1;i<temp.length();i++)  //转换为反码
    {
        num = QString(temp[i]).toInt();
        num = !num;
        temp.replace(i,1,QString::number(num));
    }
    if(temp.right(1)=="1")  //尾数为1，需要进位
    {
        for(int i = temp.length()-1;i > 0 ;i--)
        {
            if(temp.mid(i,1)=="1")
            {
                temp3.append("0");
            }
            else
            {
                temp.replace(temp.length()-temp3.length(),temp3.length(),temp3);
                break;
            }

        }
    }
    else
    {
        temp.replace(temp.length()-1,1,"1");
    }
}

//补位
void Widget::toSameSize(QString &temp1, QString &temp2)
{
    QString temp3="";
    if(temp1.length()<temp2.length())   //补位
    {
        for(int i = temp2.length()-temp1.length();i>0;i--)
        {
            temp3.append("0");
        }
        temp1.insert(1,temp3);
    }
    temp3="";
    if(temp1.length()>temp2.length())   //补位
    {
        for(int i = temp1.length()-temp2.length();i>0;i--)
        {
            temp3.append("0");
        }
        temp2.insert(1,temp3);
    }
}

//加法
void Widget::add(QString &temp1, QString &temp2)
{
    QString temp3;
    int num;
    myStack3.clear();
    for(int i = 0;i < temp2.length() ;i++)  //保存第二个数中1的位数
    {
        temp3="1";
        if(temp2.mid(i,1)=="1")
        {
            for(int j=temp2.length()-i-1;j>0;j--)
            {
                temp3.append("0");

            }
            myStack3.push(temp3);
        }
    }
    temp3="";
    while(!myStack3.isEmpty())
    {
        cout<<myStack3;
        cout<<temp1;
        temp3=myStack3.top();
//        myStack3.pop();
        num=temp3.length();
        if(temp1.mid(temp1.length()-num,1)=="0")
        {
            temp1.replace(temp1.length()-num,1,"1");
            myStack3.pop();
            cout<<temp1;
            continue;
        }
        else if(temp1.mid(temp1.length()-num,1)=="1")
        {

            temp1.replace(temp1.length()-num,1,"0");
            if(temp1.length()-num==0)
            {
                temp1.insert(0,"0");
            }
            temp3.append("0");
            myStack3.pop();
            myStack3.push(temp3);
            cout<<myStack3;
            cout<<temp1;
            continue;
        }
    }
}

//连符号位取反
void Widget::toOpposite(QString &temp)
{
    int num;
    QString temp1="1";
    for(int i = 0;i<temp.length();i++) //取反
    {
        num = QString(temp[i]).toInt();
        num = !num;
        temp.replace(i,1,QString::number(num));
    }
    if(temp.right(1)=="1")  //尾数为1，需要进位
    {
        for(int i = temp.length()-1;i > 0 ;i--)
        {
            if(temp.mid(i,1)=="1")
            {
                temp1.append("0");
            }
            else
            {
                temp.replace(temp.length()-temp1.length(),temp1.length(),temp1);
                break;
            }

        }
    }
    else
    {
        temp.replace(temp.length()-1,1,"1");
    }
}

//取反
void Widget::toUOpposite(QString &temp)
{
    int num;
    for(int i = 1;i<temp.length();i++) //取反
    {
        num = QString(temp[i]).toInt();
        num = !num;
        temp.replace(i,1,QString::number(num));
    }
}



//首页按钮
void Widget::on_pushButtonLogin_clicked()
{
    static int num=0;
    if(num<3)
    {
        QString pw=ui->passwordEdit->text();
        if(pw=="123")
        {
            ui->pushButtonPage0_1->setEnabled(true);
            ui->pushButtonPage0_2->setEnabled(true);
            ui->pushButtonPage0_3->setEnabled(true);
            ui->pushButtonPage0_4->setEnabled(true);
            QMessageBox::warning(this,"成功","密码正确！",QMessageBox::Ok,QMessageBox::NoButton);
            ui->stackedWidget->setCurrentIndex(5);
            ui->label->setText("帮助");
            num=0;
        }
        else
        {
            num++;
            QMessageBox::warning(this,"错误","密码错误！超过3次将冻结功能！",QMessageBox::Ok,QMessageBox::NoButton);
        }
    }

}

//转到逻辑运算页
void Widget::on_pushButtonPage0_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label->setText("逻辑运算");
}

//定点整数单符号位补码加减法页
void Widget::on_pushButtonPage0_2_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  ui->label->setText("定点整数单符号位补码加减运算");
}

//定点整数补码乘法页
void Widget::on_pushButtonPage0_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->label->setText("定点整数补码乘运算");
}

//浮点加减法页
void Widget::on_pushButtonPage0_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->label->setText("浮点加减运算");
}

//第一页
//逻辑非
void Widget::on_pushButtonPage1_Non_clicked()
{
    QString temp1 = ui->lineEditPage1_1->text();

        if(isTwo(temp1))    //是否为二进制
        {
            for(int i=0;i<temp1.length();i++)   //取反
            {
                if(temp1[i]=='0')
                {
                    temp1[i]='1';
                }
                else
                {
                    temp1[i]='0';
                }
            }

            ui->lineEditPage1_3->setText(temp1);
        }



}

//逻辑加
void Widget::on_pushButtonPage1_Create_clicked()
{
     QString temp1 = ui->lineEditPage1_1->text();
     QString temp2 = ui->lineEditPage1_2->text();
     QString temp3;
     QChar num1,num2;
     if(isTwo(temp1)&&isTwo(temp2))
     {
         for(int i=0;i<temp1.length();i++)  //入栈
         {
             myStack1.push(temp1[i]);
         }
         for(int i=0;i<temp2.length();i++)  //入栈
         {
             myStack2.push(temp2[i]);
         }
         while((!myStack1.isEmpty())&&(!myStack2.isEmpty()))
         {
            num1=myStack1.top();
            myStack1.pop();
            num2=myStack2.top();
            myStack2.pop();
            if(num1=='0' && num2=='0')
            {
                temp3.insert(0,"0");
            }
            else
            {
                temp3.insert(0,"1");
            }
         }
         if(!myStack1.isEmpty())    //如果第一个数位比较长，则将栈内的内容全部输出
         {
             while(!myStack1.isEmpty())
             {
                 temp3.insert(0,myStack1.top());
                 myStack1.pop();
             }
         }
         if(!myStack2.isEmpty())    //如果第二个数位比较长，则将栈内的内容全部输出
         {
             while(!myStack2.isEmpty())
             {
                 temp3.insert(0,myStack2.top());
                 myStack2.pop();
             }
         }

         ui->lineEditPage1_3->setText(temp3);
     }

}

//逻辑乘
void Widget::on_pushButtonPage1_Mul_clicked()
{
    QString temp1 = ui->lineEditPage1_1->text();
    QString temp2 = ui->lineEditPage1_2->text();
    QString temp3;
    QChar num1,num2;
    if(isTwo(temp1)&&isTwo(temp2))
    {
        for(int i=0;i<temp1.length();i++)  //入栈
        {
            myStack1.push(temp1[i]);
        }
        for(int i=0;i<temp2.length();i++)  //入栈
        {
            myStack2.push(temp2[i]);
        }
        while((!myStack1.isEmpty())&&(!myStack2.isEmpty()))
        {
           num1=myStack1.top();
           myStack1.pop();
           num2=myStack2.top();
           myStack2.pop();
           if(num1=='1' && num2=='1')
           {
               temp3.insert(0,"1");
           }
           else
           {
               temp3.insert(0,"0");
           }
        }
        if(!myStack1.isEmpty())    //如果第一个数位比较长，则将栈内的内容全部输出
        {
            while(!myStack1.isEmpty())
            {
                temp3.insert(0,"0");
                myStack1.pop();
            }
        }
        if(!myStack2.isEmpty())    //如果第二个数位比较长，则将栈内的内容全部输出
        {
            while(!myStack2.isEmpty())
            {
                temp3.insert(0,"0");
                myStack2.pop();
            }
        }

        ui->lineEditPage1_3->setText(temp3);
    }

}

//逻辑异
void Widget::on_pushButtonPage1_Exc_clicked()
{
    QString temp1 = ui->lineEditPage1_1->text();
    QString temp2 = ui->lineEditPage1_2->text();
    QString temp3;
    int num;
    QChar num1,num2;
    if(isTwo(temp1)&&isTwo(temp2))
    {
        for(int i=0;i<temp1.length();i++)  //入栈
        {
            myStack1.push(temp1[i]);
        }
        for(int i=0;i<temp2.length();i++)  //入栈
        {
            myStack2.push(temp2[i]);
        }
        while((!myStack1.isEmpty())&&(!myStack2.isEmpty()))
        {
           num1=myStack1.top();
           myStack1.pop();
           num2=myStack2.top();
           myStack2.pop();
           num = QString(num1).toInt()^QString(num2).toInt();
           temp3.insert(0,QString::number(num));
        }
        if(!myStack1.isEmpty())    //如果第一个数位比较长，则将栈内的内容全部输出
        {
            while(!myStack1.isEmpty())
            {
                temp3.insert(0,"1");
                myStack1.pop();
            }
        }
        if(!myStack2.isEmpty())    //如果第二个数位比较长，则将栈内的内容全部输出
        {
            while(!myStack2.isEmpty())
            {
                temp3.insert(0,"1");
                myStack2.pop();
            }
        }
        ui->lineEditPage1_3->setText(temp3);
    }

}

//输入
void Widget::on_pushButtonPage1_Input_clicked()
{
    if((false == ui->pushButtonPage1_Exc->isEnabled()))
    {
        ui->pushButtonPage1_Exc->setEnabled(true);
        ui->pushButtonPage1_Mul->setEnabled(true);
        ui->pushButtonPage1_Non->setEnabled(true);
        ui->pushButtonPage1_Create->setEnabled(true);
        ui->lineEditPage1_1->setFocus();
    }
}

//返回
void Widget::on_pushButtonPage1_return_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label->setText("帮助");
}

//第二页
//输入
void Widget::on_pushButtonPage2_Input_clicked()
{
    if(false == ui->pushButtonPage2_Del->isEnabled())
    {
        ui->pushButtonPage2_Del->setEnabled(true);
        ui->pushButtonPage2_Plus->setEnabled(true);
        ui->lineEditPage2_1->setFocus();
    }

}

//返回
void Widget::on_pushButtonPage2_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label->setText("帮助");
}

//加法
void Widget::on_pushButtonPage2_Plus_clicked()
{
    QString temp1 = ui->lineEditPage2_1->text();
    QString temp2 = ui->lineEditPage2_2->text();
    QString temp3 = "1";
    QString temp4;
    QChar cp_temp1,cp_temp2;
    int temp1Size;
    if(temp1.length()==8 && temp2.length()==8)
    {
        if(isTwo(temp1) && isTwo(temp2))
        {
//            if(temp1[0]=="1")   //为负数
//            {
//                toComplement(temp1);
//            }

//            temp3="1";
//            if(temp2[0]=="1")   //temp2为负数
//            {
//                toComplement(temp2);
//            }

            temp1Size=temp1.length();   //保存第一个数的长度，用于比较
            cp_temp1=temp1[0];  //保存符号位
            cp_temp2=temp2[0];


            add(temp1,temp2);   //相加

            cout<<temp1;
            cout<<cp_temp1<<cp_temp2;
            if(temp1Size==temp1.length())   //检查是否溢出
            {
                if(cp_temp1==cp_temp2)
                {
                    if(cp_temp1!=temp1[0])
                    {
                        QMessageBox::warning(this,"错误","计算溢出！",QMessageBox::Ok,QMessageBox::NoButton);
                        return;
                    }
                }
            }
            else
            {
                if(cp_temp1==cp_temp2)
                {
                    if(temp1.mid(0,2)=="10" || temp1.mid(0,2)=="01")
                    {
                        QMessageBox::warning(this,"错误","计算溢出！",QMessageBox::Ok,QMessageBox::NoButton);
                        return;
                    }
                }
            }
            //转回原码
            if(temp1Size!=temp1.length())   //丢掉溢出位
            {
                temp1.remove(0,1);
            }
//            if(temp1.mid(0,1)=="1") //如果为负数，需要减一，取反
//            {
//                temp3="1";
//                temp4="";
//                if(temp1.length()>temp3.length())   //补位，补1，
//                {
//                    for(int i = temp1.length()-temp3.length();i>0;i--)
//                    {
//                        temp4.append("1");
//                    }
//                    temp3.insert(1,temp4);
//                }
//                cout<<temp3;
//                add(temp1,temp3);
//                toUOpposite(temp1);

//            }
            ui->lineEditPage2_3->setText(temp1);

        }
    }
    else
    {
        QMessageBox::warning(this,"错误","请输入八位二进制数！",QMessageBox::Ok,QMessageBox::NoButton);
    }

}

//减法
void Widget::on_pushButtonPage2_Del_clicked()
{

    QString temp1 = ui->lineEditPage2_1->text();
    QString temp2 = ui->lineEditPage2_2->text();
    QString temp3 = "1";
    QString temp4;
    QChar cp_temp1,cp_temp2;    //保存符号位
    int temp1Size;
    if(temp1.length()==8 &&temp2.length()==8)
    {
        if(isTwo(temp1) && isTwo(temp2))
        {
            cp_temp2=temp2[0];  //保存第二个数符号位
            if(temp2.mid(0,1)=="0")
            {
                temp2.replace(0,1,"1");
            }
            else
            {
                temp2.replace(0,1,"0");
            }
            cout<<temp2;
//            if(temp1[0]=="1")   //为负数
//            {
//                toComplement(temp1);
//    //            cout<<temp1;
//            }

            temp3="1";
            if(temp2[0]=="1")   //temp2为负数
            {
               toComplement(temp2);
                cout<<temp2;
            }




    //        cout<<temp2;


            //被减数取反
//            toOpposite(temp2);

            temp1Size=temp1.length();   //保存第一个数的长度，用于比较

            cp_temp1=temp1[0];  //保存符号位
    //        cout<<temp1;
    //        cout<<temp2;

            add(temp1,temp2);   //相加

            cout<<temp1;
            if(temp1Size==temp1.length())   //检查是否溢出
            {
                if(cp_temp1!=cp_temp2)
                {
                    if(cp_temp1!=temp1[0])
                    {
                        QMessageBox::warning(this,"错误","计算溢出！",QMessageBox::Ok,QMessageBox::NoButton);
                        return;
                    }
                }

            }
            else
            {
                if(cp_temp1!=cp_temp2)
                {
                    if(temp1.mid(0,2)=="10" || temp1.mid(0,2)=="01")
                    {
                        QMessageBox::warning(this,"错误","计算溢出！",QMessageBox::Ok,QMessageBox::NoButton);
                        return;
                    }
                }
            }

            //转回原码
            if(temp1Size!=temp1.length())   //丢掉溢出位
            {
                temp1.remove(0,1);
            }
//            if(temp1.mid(0,1)=="1") //如果为负数，需要减一，取反
//            {
//                temp3="1";
//                temp4="";
//                if(temp1.length()>temp3.length())   //补位，补1，
//                {
//                    for(int i = temp1.length()-temp3.length();i>0;i--)
//                    {
//                        temp4.append("1");
//                    }
//                    temp3.insert(1,temp4);
//                }
//                cout<<temp3;
//                add(temp1,temp3);
//                if(temp1Size!=temp1.length())   //丢掉溢出位
//                {
//                    temp1.remove(0,1);
//                }
//                cout<<temp1;
//                toUOpposite(temp1);
//                cout<<temp1;

//            }
            ui->lineEditPage2_4->setText(temp1);

        }
    }
    else
    {
        QMessageBox::warning(this,"错误","请输入八位二进制数！",QMessageBox::Ok,QMessageBox::NoButton);
    }
}

//第三页

//输入
void Widget::on_pushButtonPage3_Input_clicked()
{
    ui->pushButtonPage3_Mul->setEnabled(true);
    ui->lineEditPage3_1->setFocus();
}

//返回
void Widget::on_pushButtonPage3_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label->setText("帮助");
}

//乘法
void Widget::on_pushButtonPage3_Mul_clicked()
{
    QString temp1 = ui->lineEditPage3_1->text();
    QString temp2 = ui->lineEditPage3_2->text();
    QString temp3="0";
    QString temp4="0";
    QString temp5;
    int num;
    QString cp_temp1,cp_temp2;

    if(isTwo(temp1)&&isTwo(temp2))
    {
        cp_temp1=temp1.mid(0,1);
        cp_temp2=temp2.mid(0,1);       

        temp1.replace(0,1,"0");
        temp2.replace(0,1,"0");
        toSameSize(temp1,temp3);
        toSameSize(temp1,temp4);
//        cout<<temp2;
        for(int i=temp2.length();i>0;i--)
        {
//            cout<<temp2;
            temp5=temp3.mid(0,temp2.length());
            if(temp2.mid(temp2.length()-1,1)=="1")
            {
                add(temp5,temp1);
//                cout<<temp5;
                temp3.replace(0,temp2.length(),temp5);
//                cout<<temp3;
                temp3.insert(0,"0");
                temp2.insert(0,"0");
                temp2.chop(1);
            }
            else
            {
                add(temp5,temp4);
//                cout<<temp5;
                temp3.replace(0,temp2.length(),temp5);
//                cout<<temp3;
                temp3.insert(0,"0");
                temp2.insert(0,"0");
                temp2.chop(1);
            }
        }
        num=cp_temp1.toInt()^cp_temp2.toInt();
//        cout<<num;
        temp3.replace(0,1,QString::number(num));        
        ui->lineEditPage3_3->setText(temp3);

    }
}

//第四页
void Widget::toDecimal(QString &str)
{
    float numD=0;
    for(int i=str.length();i>1;i--)
    {
        if(str.mid(i-1,1)=="1")
        {
            numD += pow(2,str.length()-i);
        }
    }
    if(str.mid(0,1)=="1")
    {
        str=QString::number(numD);
        str.insert(0,"-");
    }
    else
    {
        str=QString::number(numD);
        str.insert(0,"+");
    }
}

void Widget::toPDecimal(QString &str)
{
    float numD=0;
    for(int i=str.length();i>1;i--)
    {
        if(str.mid(i-1,1)=="1")
        {
            numD += pow(2,-(i-1));
        }
    }
    if(str.mid(0,1)=="1")
    {
        str=QString::number(numD);
        str.insert(0,"-");
    }
    else
    {
        str=QString::number(numD);
        str.insert(0,"+");
    }
}

void Widget::toBinary(QString &str)
{
    float temp=str.toFloat();
    float num;
    num=str.toInt();
    toB(abs(num));
//    myStack4.push(1);
    cout<<myStack4;
    str="";
    while(!myStack4.isEmpty())
    {
        str.insert(0,QString::number(myStack4.top()));
        myStack4.pop();
    }
    if(temp<0)
    {
        str.insert(0,"-");
    }
    else
    {
        str.insert(0,"+");
    }

}

void Widget::toPBinary(QString &str)
{
    float temp=str.toFloat();
    float num;
    num=str.toFloat();
    cout<<num;
    toPB(fabs(num));
//    myStack4.push(1);
    cout<<myStack4;
    str="";
    while(!myStack4.isEmpty())
    {
        str.insert(0,QString::number(myStack4.top()));
        myStack4.pop();
    }
    if(temp<0)
    {
        str.insert(0,"-");
    }
    else
    {
        str.insert(0,"+");
    }
}

void Widget::toB(int d)
{

    if(d/2)
    {
        toB(d/2);
    }
    if(d/2==0)
    {
        myStack4.push(1);
    }
    else
    {
        myStack4.push(d%2);
    }

}

void Widget::toPB(float d)
{
    float one=1.0;
    cout<<d;
    cout<<(d-one);
    while((d-one)!=float(0))
    {
        d *= float(2.0);
        cout<<d;
        if(d>1.0)
        {
            d -= 1.0;
            myStack4.push(1);
        }
        else if(d<1.0)
        {
            myStack4.push(0);
        }
        cout<<d;

    }
    myStack4.push(1);

}

//输入
void Widget::on_pushButtonPage4_Input_clicked()
{
    ui->pushButtonPage4_Plus->setEnabled(true);
    ui->pushButtonPage4_Del->setEnabled(true);
    ui->lineEditPage4_1->setFocus();
}

//返回
void Widget::on_pushButtonPage4_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label->setText("帮助");
}

//加法
void Widget::on_pushButtonPage4_Plus_clicked()
{
    QString order1 = ui->lineEditPage4_1->text();    //第一个数的阶码
    QString temp1 = ui->lineEditPage4_2->text();   //第一个数的尾码
    QString order2 = ui->lineEditPage4_3->text();    //第二个数的阶码
    QString temp2 = ui->lineEditPage4_4->text();   //第二个数的尾码
    QString cp_order1=order1;
    QString cp_order2=order2;
    QString tempSize;
    QString numD1Size;
    float numD1,numD2;  //浮点数
    int numD;

    if(isTwo(temp1)&&isTwo(temp2)&&isTwo(order1)&&isTwo(order2))
    {
        toPDecimal(temp1);
        toPDecimal(temp2);
        numD1=temp1.toFloat();
        numD2=temp2.toFloat();
        cout<<temp1;
        cout<<temp2;
        cout<<numD1;
        cout<<numD2;
        while(fabsf(numD1)>=1)
        {
            numD1= numD1/10;
        }
        while(fabsf(numD2)>=1)
        {
            numD2 = numD2/10;
        }
        cout<<numD1;
        cout<<numD2;

        //对阶
        toDecimal(cp_order1);
        toDecimal(cp_order2);

        if(cp_order1.toInt()>cp_order2.toInt())     //计算阶码差值
        {
            numD = cp_order1.toInt()-cp_order2.toInt();
            cout<<numD;
            while(numD!=0)
            {
                numD2 = numD2/10;
                numD--;

            }
            cout<<numD2;


        }
        else if(cp_order1.toInt()<cp_order2.toInt())
        {
            numD= cp_order2.toInt()-cp_order1.toInt();
            cp_order1=cp_order2;
            cout<<cp_order1;
            while(numD!=0)
            {
                numD1 = numD1/10;
                numD--;
            }
            cout<<numD1;
        }

        //求和
        numD1 = numD1+numD2;
        cout<<numD1;
        if(fabsf(numD1)>=1)  //需要右规
        {

            while(fabsf(numD1)>=1)
            {
                numD1-=1.0;
                numD1=numD1/2;
                numD1+=1.0;
                numD1=numD1/10;
            }
            numD=cp_order1.toInt(); //取大的阶码
            numD++;         //阶码加一
            cp_order1=QString::number(numD);
        }

        cout<<cp_order1;
        cout<<numD1;

        cout<<cp_order1;


        numD1Size=QString("%1").arg(numD1); //转换2
        cout<<numD1Size.length();
//        if(numD1>0)
//        {
//            for(int i = 1;i<=numD1Size.length()-2;i++)
//            {
//                numD1*=10;
//            }
//        }
//        else
//        {
//            for(int i = 1;i<=numD1Size.length()-3;i++)
//            {
//                numD1*=10;
//            }
//        }
        toPBinary(numD1Size);
        numD=cp_order1.toInt();
        if(numD1Size.mid(1,1)=="0") //左规
        {
            while(numD1Size.mid(1,1)=="0")
            {
                numD--;
                numD1Size.remove(1,1);
                numD1Size.append("0");
            }
        }
        cp_order1=QString::number(numD);
        toBinary(cp_order1);

        cout<<numD1;
        numD1Size.insert(1,"0.");
        ui->lineEditPage4_5->setText(cp_order1);
        ui->lineEditPage4_6->setText(numD1Size);

    }

}

//减法
void Widget::on_pushButtonPage4_Del_clicked()
{
    QString order1 = ui->lineEditPage4_1->text();    //第一个数的阶码
    QString temp1 = ui->lineEditPage4_2->text();   //第一个数的尾码
    QString order2 = ui->lineEditPage4_3->text();    //第二个数的阶码
    QString temp2 = ui->lineEditPage4_4->text();   //第二个数的尾码
    QString cp_order1=order1;
    QString cp_order2=order2;
    QString tempSize;
    QString numD1Size;
    float numD1,numD2;  //浮点数
    int numD;

    if(isTwo(temp1)&&isTwo(temp2)&&isTwo(order1)&&isTwo(order2))
    {
        if(temp2.mid(0,1)=="1")
        {
            temp2.replace(0,1,"0");
        }
        else
        {
            temp2.replace(0,1,"1");
        }

        toPDecimal(temp1);
        toPDecimal(temp2);
        numD1=temp1.toFloat();
        numD2=temp2.toFloat();
        cout<<temp1;
        cout<<temp2;
        cout<<numD1;
        cout<<numD2;
        while(fabsf(numD1)>=1)
        {
            numD1= numD1/10;
        }
        while(fabsf(numD2)>=1)
        {
            numD2 = numD2/10;
        }
        cout<<numD1;
        cout<<numD2;

        //对阶
        toDecimal(cp_order1);
        toDecimal(cp_order2);

        if(cp_order1.toInt()>cp_order2.toInt())     //计算阶码差值
        {
            numD = cp_order1.toInt()-cp_order2.toInt();
            cout<<numD;
            while(numD!=0)
            {
                numD2 = numD2/10;
                numD--;

            }
            cout<<numD2;


        }
        else if(cp_order1.toInt()<cp_order2.toInt())
        {
            numD= cp_order2.toInt()-cp_order1.toInt();
            cp_order1=cp_order2;
            cout<<cp_order1;
            while(numD!=0)
            {
                numD1 = numD1/10;
                numD--;
            }
            cout<<numD1;
        }

        //求和
        numD1 = numD1+numD2;
        if(fabsf(numD1)>=1)  //需要右规
        {
            while(fabsf(numD1)>=1)
            {
                numD1=numD1/10;
            }
            numD=cp_order1.toInt(); //取大的阶码
            numD++;         //阶码加一
            cp_order1=QString::number(numD);
        }

        cout<<cp_order1;
        cout<<numD1;
        cout<<cp_order1;


        numD1Size=QString("%1").arg(numD1); //转换2
        cout<<numD1Size.length();
//        if(numD1>0)
//        {
//            for(int i = 1;i<=numD1Size.length()-2;i++)
//            {
//                numD1*=10;
//            }
//        }
//        else
//        {
//            for(int i = 1;i<=numD1Size.length()-3;i++)
//            {
//                numD1*=10;
//            }
//        }
        toPBinary(numD1Size);
        numD=cp_order1.toInt();
        if(numD1Size.mid(1,1)=="0") //左规
        {
            while(numD1Size.mid(1,1)=="0")
            {
                numD--;
                numD1Size.remove(1,1);
                numD1Size.append("0");
            }
        }
        cp_order1=QString::number(numD);
        toBinary(cp_order1);

        cout<<numD1;
        numD1Size.insert(1,"0.");
        ui->lineEditPage4_7->setText(cp_order1);
        ui->lineEditPage4_8->setText(numD1Size);
    }
}
