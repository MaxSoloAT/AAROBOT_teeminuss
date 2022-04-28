#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int step_size;
    int x = 0, y = 0, z = 0;
private slots:
    void on_Three_radio_clicked();

    void on_Two_radio_clicked();

    void on_One_radio_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_PX_button_clicked();

    void on_MX_button_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_Open_button_clicked();

    void on_Close_button_clicked();

    void on_PY_button_clicked();

    void on_MY_button_clicked();

    void on_PZ_button_clicked();

    void on_MZ_button_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *arduino;
    static const quint16 vendor_id = 9025;
    static const quint16 product_id = 67;
    QString arduino_port;
};
#endif // WIDGET_H
