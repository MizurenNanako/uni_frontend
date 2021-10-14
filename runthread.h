#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QThread>
#include <QObject>
#include <QWidget>

class RunThread : public QThread
{
private:
    int scale_ratio;
    QString picpath;
    QString append_str;
    QString backend_path;

public:
    explicit RunThread(QObject *parent = nullptr);
    void run() override();
    void setParam(const QString &picpath,
                  const QString &backend_path,
                  const QString &model_path,
                  const QString &append_str,
                  const int scale_ratio);
};

#endif // RUNTHREAD_H
