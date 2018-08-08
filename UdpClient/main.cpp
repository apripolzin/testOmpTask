#include <QApplication>
#include "clientmainwindow.h"

void messageHandler(QtMsgType, const QMessageLogContext &, const QString &msg){
    ClientMainWindow::getInstance()->logMessage(msg);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ClientMainWindow::getInstance()->show();

    return a.exec();
}
