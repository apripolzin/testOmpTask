#include <QApplication>
#include "servermainwindow.h"

void messageHandler(QtMsgType, const QMessageLogContext &, const QString &msg){
    ServerMainWindow::getInstance()->logMessage(msg);
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(&messageHandler);
    QApplication a(argc, argv);
    ServerMainWindow::getInstance()->show();
    return a.exec();
}
