#include "mainwindow.h"
#include <QApplication>
#include <QRegExp>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*
    QRegExp rx("_result([\\S\\s]+)result_");
    QString str = "_resultOffsets: {12} d1\n ksjdkl \t jjks \n4d 99 231 7result_";
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    qDebug()<<list;
*/
    return a.exec();
}
