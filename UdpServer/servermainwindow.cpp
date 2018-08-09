#include "servermainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QApplication>
#include <QFile>
#include <QPushButton>
#include <QMessageBox>

ServerMainWindow *ServerMainWindow::pInstance = nullptr;

ServerMainWindow::ServerMainWindow(QWidget *parent) : QWidget(parent),
    downloadDir(QApplication::applicationDirPath() + "/Download"), interval(300)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    teLog = new QTextEdit;
    mainLayout->addWidget(teLog);
    this->setLayout(mainLayout);

    serverSocket = new QUdpSocket(this);

    QString uploadedFilePath = downloadDir.absolutePath() + "/uploaded.compressed";

    timer = new QTimer;
    connect(timer, &QTimer::timeout, [=](){
        //Sending datagram to client
        QFile uploadedFile(uploadedFilePath);
        uploadedFile.open(QIODevice::ReadOnly);
        qint64 size = uploadedFile.size();
        qDebug() << "Sending received data size" << size;
        QByteArray baDatagram;
        QDataStream out(&baDatagram, QIODevice::WriteOnly);
        out << size;

        serverSocket->writeDatagram(baDatagram, QHostAddress::LocalHost, 777);
    });
    timer->start(interval);

    if (!downloadDir.exists()){
        downloadDir.mkpath(downloadDir.absolutePath());
    }

    fileReceiveSocket = new QUdpSocket;
    fileReceiveSocket->bind(771);
    connect(fileReceiveSocket, &QUdpSocket::readyRead, [=](){
        QFile uploadedFile(uploadedFilePath);

        if (!uploadedFile.open(QIODevice::Append)){
            qDebug() << "Error opening to append" << uploadedFile.fileName();
            return;
        }

        while (fileReceiveSocket->hasPendingDatagrams()) {
            uploadedFile.write(fileReceiveSocket->receiveDatagram().data());
            qApp->processEvents();
        }
    });

    QPushButton *pbUncompress = new QPushButton("Uncompress");
    mainLayout->addWidget(pbUncompress);
    connect(pbUncompress, &QPushButton::clicked, [=](){
        timer->stop();
        QFile uploadedFile(uploadedFilePath);
        QFile uncompressedFile(downloadDir.absolutePath() + "/uncompressed.pdf");

        if (!uploadedFile.open(QIODevice::ReadOnly)){
            QMessageBox::critical(nullptr, "Unable to open file", QString("Unable to open file %1 for read").arg(uploadedFile.fileName()));
            timer->start(interval);
            return;
        }

        if (!uncompressedFile.open(QIODevice::WriteOnly)){
            QMessageBox::critical(nullptr, "Unable to open file", QString("Unable to open file %1 for write").arg(uncompressedFile.fileName()));
            timer->start(interval);
            return;
        }
        uncompressedFile.write(qUncompress(uploadedFile.readAll()));
        timer->start(interval);
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
