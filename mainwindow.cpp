#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    recvThread = new MyThread();


    ui->btn_start->setShortcut(Qt::Key_Return); //设置快捷键为大键盘enter键

    //更新UI
    connect(recvThread, SIGNAL(sendMessage(QString)),
               this, SLOT(receiveMessage(QString)));

    //获取输入命令，传送给子线程
    connect(this, SIGNAL(sendCMD(QString)),
               recvThread, SLOT(recvCMD(QString)));

    connect(this, SIGNAL(init_signal()), recvThread, SLOT(init()));
    emit init_signal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
    QString cmd = ui->lineEdit_cmd->text();
   // cmd = "appetizer.exe " + cmd;
    emit sendCMD(cmd);
    ui->lineEdit_cmd->clear();
    recvThread->start();
}

void MainWindow::receiveMessage(const QString &str)
{
    if(str.isEmpty())
    {
        QString info = "指令输入有误!";
        ui->textEdit_recv->append(info);
        qDebug()<<"empty";
    }
    else{
    ui->textEdit_recv->append(str);
    }
    qDebug()<<"changed";
}
