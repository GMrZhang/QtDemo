#include "ThreadFromQThread.h"
#include <QDebug>
ThreadFromQThread::ThreadFromQThread(QObject* par) : QThread(par)
,m_runCount(20)
{
    mIsStop = false;
}

ThreadFromQThread::~ThreadFromQThread()
{
    qDebug() << "ThreadFromQThread::~ThreadFromQThread()";
}

void ThreadFromQThread::setSomething()
{
    msleep(500);
    QString str = QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg(reinterpret_cast<int>(QThread::currentThreadId()));
    emit message(str);
}

void ThreadFromQThread::getSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg(reinterpret_cast<int>(QThread::currentThreadId())));
}

void ThreadFromQThread::setRunCount(int count)
{
    m_runCount = count;
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg(reinterpret_cast<int>(QThread::currentThreadId())));
}

void ThreadFromQThread::run()
{
    int count = 0;
    QString str = QString("%1->%2,thread id:%3").arg(__FILE__).arg(__FUNCTION__).arg(reinterpret_cast<int>(QThread::currentThreadId()));
    emit message(str);
    while(1)
    {
        QMutexLocker lock(&mMutex);
        if(mIsStop == true )
        {
            return;
        }
        sleep(1);
        ++count;
        emit progress( ( static_cast<float>(count) / m_runCount)*100 );
        emit message(QString("ThreadFromQThread::run times:%1").arg(count));
        doSomething();
        if(m_runCount == count)
        {
            break;
        }
    }
}

void ThreadFromQThread::stop()
{
    QMutexLocker lock(&mMutex);
    mIsStop = true;

}

void ThreadFromQThread::doSomething()
{
    msleep(500);
    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg(reinterpret_cast<int>(QThread::currentThreadId())));
}
