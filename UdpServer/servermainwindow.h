#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QWidget>

class ServerMainWindow : public QWidget
{
    Q_OBJECT
public:
    ServerMainWindow(QWidget *parent = nullptr);
    virtual ~ServerMainWindow() override;

};

#endif // SERVERMAINWINDOW_H
