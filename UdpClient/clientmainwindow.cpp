#include "clientmainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QNetworkDatagram>

ClientMainWindow *ClientMainWindow::pInstance = nullptr;

ClientMainWindow::ClientMainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    teLog = new QTextEdit;
    mainLayout->addWidget(teLog);
    this->setLayout(mainLayout);

    clientSocket = new QUdpSocket;
    clientSocket->bind(777);

    connect(clientSocket, &QUdpSocket::readyRead, [=](){
        while (clientSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = clientSocket->receiveDatagram();
            qDebug() << "Received" << datagram.data();
        }
    });
}

ClientMainWindow::~ClientMainWindow()
{
}

ClientMainWindow *ClientMainWindow::getInstance()
{
    if (!pInstance)
        pInstance = new ClientMainWindow();
    return pInstance;
}

void ClientMainWindow::logMessage(const QString &mes)
{
    teLog->moveCursor(QTextCursor::Start);
    teLog->append(mes + "\n");
}

