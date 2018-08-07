#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QWidget>
#include <QUdpSocket>
#include <QPointer>
#include <QDoubleSpinBox>
#include <QPushButton>

class ServerMainWindow : public QWidget
{
    Q_OBJECT
public:
    ServerMainWindow(QWidget *parent = nullptr);
    virtual ~ServerMainWindow() override;

protected:
    QPointer<QUdpSocket>     serverSocket;
    QPointer<QDoubleSpinBox> dsbPort;
    QPointer<QPushButton>    pbBind;

private slots:
    void readPendingDatagrams();

};

#endif // SERVERMAINWINDOW_H
