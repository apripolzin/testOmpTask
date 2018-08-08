#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include <QUdpSocket>
#include <QTextEdit>

class ClientMainWindow : public QWidget
{
    Q_OBJECT

private:
    explicit ClientMainWindow(QWidget *parent = nullptr);

public:    
    virtual ~ClientMainWindow() override;

private:
    QPointer<QUdpSocket> clientSocket;
    QPointer<QTextEdit> teLog;

private:
    static ClientMainWindow* pInstance;

public:
    static ClientMainWindow *getInstance();

public:
    void logMessage(const QString &mes);

};

#endif // CLIENTMAINWINDOW_H
