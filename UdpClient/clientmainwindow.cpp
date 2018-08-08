#include "clientmainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QNetworkDatagram>
#include <QFile>
#include <QApplication>
#include "JlCompress.h"

ClientMainWindow *ClientMainWindow::pInstance = nullptr;

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QWidget(parent),
      uploadFileName(QApplication::applicationDirPath() + "/out.pdf"),
      compressedFileName(QApplication::applicationDirPath() + "/out.zip")
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    teLog = new QTextEdit;
    pbProgress = new QProgressBar;
    pbProgress->setTextVisible(true);
    pbProgress->setMinimum(0);
    pbProgress->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(pbProgress);
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

    //compressFileToUpload();
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
    QFile uploadFile (uploadFileName);

    if (!uploadFile.exists()){
        qDebug() << uploadFile.fileName() << " not exists";
        return;
    }

    if (!uploadFile.open(QIODevice::ReadOnly)){
        qDebug() << "cannot open" << uploadFile.fileName();
        return;
    }

    pbProgress->setMaximum(int(uploadFile.size()));
    pbProgress->setValue(seekFrom);
    pbProgress->setFormat(QString("%1/%2").arg(seekFrom).arg(uploadFile.size()));
    if (seekFrom >= uploadFile.size()){
        pbProgress->setFormat("Comlete");
        return;
    }

    uploadFile.seek(seekFrom);
    QByteArray baDatagram = uploadFile.read(2048);
    fileSendSocket->writeDatagram(baDatagram, QHostAddress::LocalHost, 771);
}

void ClientMainWindow::compressFileToUpload()
{
    QFile compressedFile(compressedFileName);
    QFile uploadFile(uploadFileName);

    JlCompress::compressFiles(compressedFileName ,QStringList() << uploadFile.fileName());
}

