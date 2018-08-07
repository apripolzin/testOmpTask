#include "servermainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkDatagram>

ServerMainWindow::ServerMainWindow(QWidget *parent) : QWidget(parent)
{
    serverSocket = new QUdpSocket(this);

    dsbPort = new QDoubleSpinBox;
    dsbPort->setDecimals(0);
    dsbPort->setRange(0, 65535);
    dsbPort->setValue(7111);

    pbBind = new QPushButton("Bind port");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(dsbPort);
    buttonLayout->addWidget(pbBind);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    connect(pbBind, &QPushButton::clicked, [=]{
        quint16 port = quint16 (dsbPort->value());
        if (!serverSocket->bind(QHostAddress::LocalHost, port)){
            QMessageBox::critical(nullptr, "Server Error", QString("Error bind on port %1").arg(port));
            return;
        };
        pbBind->setEnabled(false);
        connect(serverSocket, &QUdpSocket::readyRead, this, &ServerMainWindow::readPendingDatagrams);
    });


}

ServerMainWindow::~ServerMainWindow()
{
}

void ServerMainWindow::readPendingDatagrams()
{
    if (serverSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = serverSocket->receiveDatagram();
        qDebug() << datagram.data();
    }
}
