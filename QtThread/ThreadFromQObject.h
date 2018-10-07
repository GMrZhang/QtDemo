#ifndef THREADFROMQOBJECT_H
#define THREADFROMQOBJECT_H

#include <QObject>
#include <QThread>
#include <QDebug>

class Worker : public QObject
{
  Q_OBJECT

public slots:
  void doWork(const QString &parameter)
  {
      QString result = parameter;
      qDebug()<<"[ Worker : doWork ] : "<< parameter;
      qDebug()<<"[ Worker : doWork ] : Id "<< QThread::currentThreadId ();
      emit resultReady(result);
  }

signals:
  void resultReady(const QString &result);
};

class Controller : public QObject
{
  Q_OBJECT
  QThread workerThread;
public:
  Controller() {
      Worker *worker = new Worker;
      worker->moveToThread(&workerThread);
      connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
      connect(this, &Controller::operate, worker, &Worker::doWork);
      connect(worker, &Worker::resultReady, this, &Controller::handleResults);
      workerThread.start();
  }
  ~Controller() {
      workerThread.quit();
      workerThread.wait();
  }

  void  testEmitSignal( QString & str )
  {
      emit operate(str);
  }

public slots:
  void handleResults(const QString &str)
  {
      qDebug()<<"[ Controller : handleResults ] : "<< str;
  }

signals:
  void operate(const QString &);
};

#endif // THREADFROMQOBJECT_H
