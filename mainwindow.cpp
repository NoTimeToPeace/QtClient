#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket())
    , statusConnected(false)
{
    ui->setupUi(this);

    // Устанавливаем окно по центру экрана
    this->setFixedHeight(150);
    this->setFixedWidth(500);
    this->setGeometry(QApplication::desktop()->screenGeometry(0).width()/2-400, QApplication::desktop()->screenGeometry(0).height()/2-175, 500, 150); // Устанавливаем окно в центр экрана

    // Устанавливаем связи
    //connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readyRead); // Для приёма сообщений с сервера
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::serverKickedMe); // При отключении клиента от сервара делаем оповещалку
    //connect(socket, &QTcpSocket::disconnected, this, &MainWindow::deleteLater);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::changeStatusConnected);
}

MainWindow::~MainWindow()
{
    //delete socket;
    delete ui;
}

// Подключение к серверу
void MainWindow::on_pushButton_2_clicked()
{
    QString ip = ui->lineEdit->text();
    int port = ui->lineEdit_2->text().toInt();
    qDebug() << socket->isValid();
    // Если не подключены, то подключаемся
    if (!statusConnected) {
        socket->connectToHost(ip, port);
        qDebug() << socket->isValid();
    } else {
        qDebug("You are already connected to the server");
    }
}

// Отправка сообщения на сервер
void MainWindow::sendToServer(QString value)
{
    // Если подключены, то отправляем сообщение
    if (statusConnected) {
        data.clear(); // Чистим от возможного мусора
        QDataStream out(&data, QIODevice::WriteOnly); // Для передачи сообщения
        out.setVersion(QDataStream::Version::Qt_5_9); // Для исключения ошибок
        out << value;

        socket->write(data);
    } else {
        qDebug() << "No connection to server.";
    }
}

//// Получаем сообщение от сервера
//void MainWindow::readyRead() {
//    QDataStream in(&data, QIODevice::ReadOnly);
//    in.setVersion(QDataStream::Version::Qt_5_9);

//    if (in.status() == QDataStream::Ok) {
//        QString value;
//        in >> value;
//        ui->label->setText(value);
//    } else {
//        ui->label->setText("Error Read");
//    }
//}

// Подключившись к серверу ставим что подключены
void MainWindow::changeStatusConnected()
{
    this->statusConnected = true;
    ui->label->setText("You are connected to the server");
}

// Когда произошел дисконнект с сервером
void MainWindow::serverKickedMe()
{
    this->statusConnected = false;
    ui->label->setText("You are disconnected from server");
}

// Отправка сообщения на сервер
void MainWindow::on_pushButton_clicked()
{
    sendToServer(ui->lineEdit_3->text());
}

