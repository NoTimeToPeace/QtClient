#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QDebug>
#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>

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
    void on_pushButton_clicked(); // Отправить сообщение
    void on_pushButton_2_clicked(); // Подключиться к серверу

private:
    void sendToServer(QString value); // Отправка сообщения на сервер

private:
    Ui::MainWindow *ui;
    QByteArray data; // Данные, которые будем передавать
    QTcpSocket *socket; // Соккет клиента
    bool statusConnected;

public slots:
    //void readyRead(); // Читаем данные, полученные от сервера
    void changeStatusConnected(); // Изменяем statusСonnected при успешном подключении
    void serverKickedMe(); // Дисконнект с сервером
};
#endif // MAINWINDOW_H
