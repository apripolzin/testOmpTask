#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QWidget>
#include <QUdpSocket>
#include <QPointer>
#include <QTextEdit>
#include <QTimer>

class ServerMainWindow : public QWidget
{
    Q_OBJECT
private:
    ServerMainWindow(QWidget *parent = nullptr);
    virtual ~ServerMainWindow() override;

private slots:
    void readPendingDatagrams();

private:
    static ServerMainWindow *pInstance;

public:
    static ServerMainWindow *getInstance();

public:
    void logMessage(const QString &msg);

private:
    QPointer<QUdpSocket> serverSocket;
    QPointer<QTextEdit> teLog;
    QPointer<QTimer> timer;

};

#endif // SERVERMAINWINDOW_H
