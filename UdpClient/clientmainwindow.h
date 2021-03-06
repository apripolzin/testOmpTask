#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include <QUdpSocket>
#include <QTextEdit>
#include <QProgressBar>

class ClientMainWindow : public QWidget
{
    Q_OBJECT

private:
    explicit ClientMainWindow(QWidget *parent = nullptr);

public:    
    virtual ~ClientMainWindow() override;

private:
    QPointer<QUdpSocket> clientSocket;
    QPointer<QUdpSocket> fileSendSocket;
    QPointer<QTextEdit> teLog;
    QPointer<QProgressBar> pbProgress;

private:
    static ClientMainWindow* pInstance;

public:
    static ClientMainWindow *getInstance();

public:
    void logMessage(const QString &mes);

private:
    void sendFileChunk(int seekFrom);

private:
    const QString uploadFileName;
    const QString compressedFileName;

private:
    void compressFileToUpload();

};

#endif // CLIENTMAINWINDOW_H
