#include "servermainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkDatagram>

ServerMainWindow *ServerMainWindow::pInstance = nullptr;

ServerMainWindow::ServerMainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    teLog = new QTextEdit;
    mainLayout->addWidget(teLog);
    this->setLayout(mainLayout);

    serverSocket = new QUdpSocket(this);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, [=](){
        qDebug() << "send hello!!";
        serverSocket->writeDatagram("Hello!!!", QHostAddress::LocalHost, 777);
    });
    timer->start(500);
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

ServerMainWindow *ServerMainWindow::getInstance()
{
    if (!pInstance)
        pInstance = new ServerMainWindow();
    return pInstance;
}

void ServerMainWindow::logMessage(const QString &msg)
{
    teLog->moveCursor(QTextCursor::Start);
    teLog->insertPlainText(msg + "\n");
}
