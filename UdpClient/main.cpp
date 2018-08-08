#include <QApplication>
#include "clientmainwindow.h"

void messageHandler(QtMsgType, const QMessageLogContext &, const QString &msg){
    ClientMainWindow::getInstance()->logMessage(msg);
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(&messageHandler);

    QApplication a(argc, argv);
    ClientMainWindow::getInstance()->show();

    return a.exec();
}
