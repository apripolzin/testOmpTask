#include "clientmainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostAddress>
#include <QDebug>

ClientMainWindow::ClientMainWindow(QWidget *parent) : QWidget(parent), uploadFileName("")
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *openFileLayout = new QHBoxLayout;

    pbOpenFile = new QPushButton("Open...");
    lblFileToSend = new QLabel(uploadFileName);
    connect(pbOpenFile, &QPushButton::clicked, [=](){
        uploadFileName = QFileDialog::getOpenFileName(this, "Open PDF file", "..", "*.pdf");
        lblFileToSend->setText(uploadFileName);
        pbUploadFile->setEnabled(true);
        connect(pbUploadFile, &QPushButton::clicked, this, &ClientMainWindow::slotUploadFile);
    });

    pbUploadFile = new QPushButton("Upload");
    if (uploadFileName == "")
        pbUploadFile->setEnabled(false);

    uploadingProgress = new QProgressBar;

    openFileLayout->addWidget(pbOpenFile);
    openFileLayout->addWidget(lblFileToSend);
    openFileLayout->addStretch();

    leServerAddress = new QLineEdit("127.0.0.1");
    dsbServerPort = new QDoubleSpinBox;
    dsbServerPort->setDecimals(0);
    dsbServerPort->setRange(0, 65535);
    dsbServerPort->setValue(7111);

    QHBoxLayout *serverSettingsLayout = new QHBoxLayout;
    serverSettingsLayout->addWidget(leServerAddress);
    serverSettingsLayout->addWidget(dsbServerPort);

    mainLayout->addLayout(openFileLayout);
    mainLayout->addLayout(serverSettingsLayout);
    mainLayout->addWidget(pbUploadFile);
    mainLayout->addWidget(uploadingProgress);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    clientSocket = new QUdpSocket;
}

ClientMainWindow::~ClientMainWindow()
{
}

void ClientMainWindow::slotUploadFile()
{
    qDebug() << clientSocket->writeDatagram(QByteArray("Hello!!!"), QHostAddress(leServerAddress->text()), quint16(dsbServerPort->value()));
}
