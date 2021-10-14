#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

const char INFORMATION[] =
        "Frontend of realsr-ncnn-like backends\n\n"
        "A version for animate pictures:\n"
        "https://github.com/xinntao/Real-ESRGAN.git\n"
        "This Frontend is written by:\n\tTomny Cui (tomnycui@outlook.com)\n"
        "Licence: GPLv2\n\n"
        "I wrote this frontend for convenience,\n"
        "and it just a request from my schoolmate.\n"
        "\t\tTomny Cui, " __DATE__;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Icz_clicked();

    void on_pushButton_Dcz_clicked();

    void on_pushButton_AddFile_clicked();

    void on_pushButton_RemoveFile_clicked();

    void on_pushButton_Run_clicked();

    void on_pushButton_Model_clicked();

    void on_pushButton_Backend_clicked();

    void on_pushButton_LogCL_clicked();

    void on_pushButton_ClearFile_clicked();

private:
    //data
    int scale_ratio = 4;
    QString backend_path = "unspecified";
    QString model_path = "unspecified";
    QStringList working_list;
    QString append_str = "out";
    //QStandardItemModel *displaying_model;
    QStandardItemModel displaying_model;
    Ui::MainWindow *ui;

    //inner function
    void uniqueoutput(const QString &context, bool notmain = false);
    void updatelistview();
};
#endif // MAINWINDOW_H
