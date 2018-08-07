#include "clientmainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

ClientMainWindow::ClientMainWindow(QWidget *parent) : QWidget(parent), uploadFileName("")
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *openFileLayout = new QHBoxLayout;

    pbOpenFile = new QPushButton("Open...");
    lblFileToSend = new QLabel(uploadFileName);
    connect(pbOpenFile, &QPushButton::clicked, [&](){
        uploadFileName = QFileDialog::getOpenFileName(this, "Open PDF file", "..", "*.pdf");
        lblFileToSend->setText(uploadFileName);
    });

    openFileLayout->addWidget(pbOpenFile);
    openFileLayout->addWidget(lblFileToSend);
    openFileLayout->addStretch();

    mainLayout->addLayout(openFileLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

ClientMainWindow::~ClientMainWindow()
{
}
