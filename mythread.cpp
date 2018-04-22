#include "mythread.h"
#include <QDebug>
#include <QProcess>
#include <QMessageBox>

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
}

MyThread::~MyThread()
{
}

void MyThread::run()
{
    QProcess process;
    running_process = &process;
    QStringList arguments;
    arguments << "/c"<<arg_cmd <<"\r\n";

    arg_cmd += "\r\n";
   // process.start("cmd.exe", arguments);
    char*ch;
    QByteArray ba = arg_cmd.toLatin1();
    ch=ba.data();

    process.start("cmd.exe");
//    process.write(ch);
    process.write("dir\n\r");
    process.write("ipconfig\n\r");
    process.write("exit\n\r");
  //   process.execute("exit");
    process.waitForStarted();
    process.waitForFinished();
    QString strResult = QString::fromLocal8Bit(process.readAllStandardOutput());

    emit sendMessage(strResult);
    qDebug()<<"send";
}

void MyThread::recvCMD(const QString &cmd)
{
    arg_cmd = cmd;
    qDebug()<<cmd;
}

void MyThread::exit_slot(){
    qDebug()<<"exit";
    running_process->close();
    running_process->write("exit\n\r");
    //running_process->start("exit");

}

void MyThread::read_slot()
{
    while(running_process->canReadLine())
       {
           char output[1024];
           int ret = running_process->readLine(output,1023);
           qDebug() << ret;
           qDebug() << output;

           QByteArray byte_output = QByteArray(output);

           QString tmpstr;
           tmpstr = QString::fromLocal8Bit(byte_output);

           emit sendMessage(tmpstr);
           qDebug()<<"send!!!";
       }
}

void MyThread::init(){
    running_process = new QProcess;
    connect(running_process,SIGNAL(readyReadStandardOutput()),this,SLOT(read_slot()));
}