#ifndef THREADFROMQTHREAD_H
#define THREADFROMQTHREAD_H
#include <QThread>
#include <QMutex>
#include <QMutexLocker>


class ThreadFromQThread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(float present);

public:
    ThreadFromQThread(QObject* par);
    ~ThreadFromQThread();
    void setSomething();
    void getSomething();
    void setRunCount(int count);
    void run();
    void stop();
    void doSomething();
private:
    int m_runCount;
    QMutex mMutex;
    bool mIsStop;
};

#endif // THREADFROMQTHREAD_H
