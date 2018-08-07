#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include <QUdpSocket>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSettings>

class ClientMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    virtual ~ClientMainWindow() override;

private:
    QPointer<QPushButton>    pbOpenFile;
    QPointer<QLabel>         lblFileToSend;
    QPointer<QPushButton>    pbUploadFile;
    QPointer<QProgressBar>   uploadingProgress;
    QPointer<QLineEdit>      leServerAddress;
    QPointer<QDoubleSpinBox> dsbServerPort;
    QPointer<QUdpSocket>     clientSocket;
    QString uploadFileName;


private slots:
    void slotUploadFile();
};

#endif // CLIENTMAINWINDOW_H
