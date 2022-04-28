#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   setFixedSize(300,200);
    ui->lineEdit->setText("0");
    ui->One_radio->setChecked(true);
    step_size = 1;
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()){
        ui->comboBox->addItem(port.portName());
    }
}

Widget::~Widget()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}


void Widget::on_Three_radio_clicked()
{
    if(ui->Three_radio->isChecked()==true){
        ui->lineEdit->setEnabled(true);
    }
}

void Widget::on_Two_radio_clicked()
{
    ui->lineEdit->setEnabled(false);
    step_size = 10;
}

void Widget::on_One_radio_clicked()
{
    ui->lineEdit->setEnabled(false);
    step_size = 1;
}

void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    step_size = arg1.toInt();
}

void Widget::on_comboBox_activated(const QString &arg1)
{
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()){
        ui->comboBox->addItem(port.portName());
    }
    //qDebug()<<arg1<<endl;
    arduino_port = arg1;
}

void Widget::on_Open_button_clicked()
{
    arduino->setPortName(arduino_port);
    arduino->open(QSerialPort::WriteOnly);
    arduino->setBaudRate(QSerialPort::Baud115200);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
}

void Widget::on_Close_button_clicked()
{
    arduino->close();
}

void Widget::on_PX_button_clicked()
{
    x+= step_size;
    QString px = "G0 X"+ QString::number(x)+"\r";
    qDebug()<<px <<endl;
    arduino->write(px.toStdString().c_str());
}

void Widget::on_MX_button_clicked()
{
    x-= step_size;
    QString mx = "G0 X"+ QString::number(x)+"\r";
    qDebug()<<mx <<endl;
    arduino->write(mx.toStdString().c_str());
}

