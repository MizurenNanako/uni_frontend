#include "runthread.h"
#include <QProcess>
#include <QDialog>

RunThread::RunThread(QObject *parent) : QThread(parent)
{
}

void RunThread::run()
{
    QProcess proc;
    proc.setProgram(backend_path);
    proc.setArguments(
                {
                    "-i", picpath,
                    "-o", picpath + append_str,
                    "-s", QString(scale_ratio),
                });
    proc.start(QProcess::OpenModeFlag::ReadOnly);
    QString picname = picpath.mid(picpath.lastIndexOf('/'));
    while (!proc.isReadable())
    {
        QThread::sleep(50); //sleep 50ms
    }
    //now the proc is started and readable
    //start a new window for output
    QWidget *pwin = new QDialog(nullptr);
    pwin->setWindowTitle(picname + " 0.0%");
    pwin->show();
    //do something...
    while (proc.state() == QProcess::ProcessState::Running)
    {
        //since proc is running and readable
        //so read its output
        QByteArray tmpoutput;
        if (proc.canReadLine())
        {
            tmpoutput = proc.readLine();
            if (tmpoutput.lastIndexOf('%') != -1)
            {
                pwin->setWindowTitle(picname + " " + tmpoutput);
            }
        }
    }
    pwin->close();
    delete pwin;
}

void RunThread::setParam(const QString &picpath,
                         const QString &backend_path,
                         const QString &model_path,
                         const QString &append_str,
                         const int scale_ratio)
{
    this->picpath = picpath;
}
