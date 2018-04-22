#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyThread *recvThread;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendCMD(const QString &);
    void init_signal();
private slots:
    void on_btn_start_clicked();
    void receiveMessage(const QString &);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
