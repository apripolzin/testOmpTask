#include "clientmainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QNetworkDatagram>
#include <QFile>
#include <QApplication>

ClientMainWindow *ClientMainWindow::pInstance = nullptr;

ClientMainWindow::ClientMainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    teLog = new QTextEdit;
    mainLayout->addWidget(teLog);
    this->setLayout(mainLayout);

    clientSocket = new QUdpSocket;
    clientSocket->bind(777);

    fileSendSocket = new QUdpSocket;

    connect(clientSocket, &QUdpSocket::readyRead, [=](){
        while (clientSocket->hasPendingDatagrams()) {
            QByteArray baDatagram;
            baDatagram.resize(int(clientSocket->pendingDatagramSize()));
            clientSocket->readDatagram(baDatagram.data(), baDatagram.size());
            QDataStream in(&baDatagram, QIODevice::ReadOnly);
            qint64 filesize;
            in >> filesize;
            qDebug() << "Received filesize " << filesize;
            this->sendFileChunk(int(filesize));
            qApp->processEvents();
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
    teLog->insertPlainText(mes + "\n");
}

void ClientMainWindow::sendFileChunk(int seekFrom)
{
    qDebug() << "sendilng from" << seekFrom;
    QFile uploadFile (QApplication::applicationDirPath() + "/out.pdf");
    if (!uploadFile.exists()){
        qDebug() << uploadFile.fileName() << " not exists";
        return;
    }

    if (!uploadFile.open(QIODevice::ReadOnly)){
        qDebug() << "cannot open" << uploadFile.fileName();
        return;
    }
    uploadFile.seek(seekFrom);
    QByteArray baDatagram = uploadFile.read(2048);
    fileSendSocket->writeDatagram(baDatagram, QHostAddress::LocalHost, 771);
}

