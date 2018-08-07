#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include <QPushButton>
#include <QString>
#include <QLabel>

class ClientMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    virtual ~ClientMainWindow() override;

private:
    QPointer<QPushButton> pbOpenFile;
    QPointer<QLabel> lblFileToSend;
    QString uploadFileName;
};

#endif // CLIENTMAINWINDOW_H
