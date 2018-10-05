#include <QApplication>
#include <QCoreApplication>  
#include <QEvent>  
#include <QObject>  
#include <QDebug>  
  
/*
 *  Qt自定义事件的要点：

    A、自定义事件必须继承自QEvent。

    B、自定义事件类必须拥有全局唯一的Type值(自定义事件可以使用QEvent:：User之后的值，并保证全局唯一)。

    C、程序必须提供处理自定义事件对象的方法,继承QObject，然后重新实现Event函数，内部增加判断自定义事件的类型

    D，使用sendEvent或postEvent发送事件，第一个参数就是步骤C中的实例
 * */

static const QEvent::Type MyEventType = static_cast<QEvent::Type>(QEvent::registerEventType(QEvent::User+100));
//长官，产生事件
class MyEvent: public QEvent  
{  
public:  
    MyEvent(Type MyEventType, QString * str = NULL):QEvent(MyEventType)
    {
        mData = str;
    }

    QString * data( void )
    {
        return mData;
    }

private:

    QString * mData;
};  
  
//信使，发送事件
class MySender: public QCoreApplication  
{  
public:  
    MySender(int argc,char *argv[]):QCoreApplication(argc,argv){}  
  
public:  
    bool notify(QObject *receiver, QEvent *event);  
  
};  
  
bool MySender::notify(QObject *receiver, QEvent *event)  
{  
    if(event->type() == MyEventType)  
    {  
        qDebug()<<"[ MySender::notify ] : MyEventType is coming!";
        //return true;  
        /*这里不能return true,因为重写notify就是在事件被向下传递之前截住它， 
        随便搞它，搞完了还得给QCoreApplication::notify向下传递，除非在mySender.notify 
        实现了事件向下传递的那一套。直接返回的话myArmy就收不到这个事件，因为执行完这个 
        mySender.notify的return true后，事件传递被人为的在半截终止了 
        （见Qt事件处理的五个层次http://blog.csdn.net/michealtx/article/details/6865891 ） 
        ，下面的myArmy的安装的过滤器和它自己的event都不会收到这个事件，更甭提最后干活 
        的myEventHandler了。所以在主函数中执行完mySender.sendEvent把myEvent 
        交给mySender.notify这个败家子儿后，就执行mySender.exec进入其它事件的循环了。这就是 
        问题http://topic.csdn.net/u/20111012/19/78036d16-c163-40f9-a05c-3b7d6f4e9043.html 
        出现的原因。感谢1+1=2大牛！非常感谢！ 
        */  
    }  
    return QCoreApplication::notify(receiver,event);  
}  
  
//军队,事件处理对象
class MyArmy: public QObject  
{  
public:  
    virtual void MyEventHandler(QEvent *event);
    virtual bool event(QEvent *event);
};  
  
void MyArmy::MyEventHandler(QEvent *event)  
{  
    qDebug()<<"[ MyArmy::MyEventHandler ] : The event is being handled!";
    event->accept();  
}  
  
bool MyArmy::event(QEvent *event)  
{  
    MyEvent * myEvent = static_cast<MyEvent *>(event);
    if(event->type() == MyEventType)  
    {  
        qDebug()<<"[ MyArmy::event ] : Event() is dispathing MyEvent";
        MyEventHandler(event);//调用事件处理函数  
        if(myEvent->isAccepted())
        {  
            qDebug()<<"[ MyArmy::event ] : The event has been handled!";
            return true;  
        }  
    }  
    return QObject::event(event);  
}  
  
//监控者，监控目标的事件，即过滤目标事件
class MyWatcher: public QObject  
{  
public:  
    bool eventFilter(QObject *watched, QEvent *event);  
};  

//每发一个事件，该函数会调用两次，一次是QApplication，一次是具体的目标对象
bool MyWatcher::eventFilter(QObject *watched, QEvent *event)  
{  
    if(event->type() == MyEventType)  
    {  
        qDebug()<<"[ MyWatcher::eventFilter ] : I don't wanna filter MyEventType";
        return false;  
    }  
    return QObject::eventFilter(watched,event);  
}  
  
  
int main(int argc, char *argv[])  
{  
    //QCoreApplication a(argc, argv);  
    MySender mySender(argc,argv);  
  
    MyArmy myArmy;  
    MyWatcher myWatcher;  
    myArmy.installEventFilter(&myWatcher);//安装具体目标的事件过滤器
    QApplication::instance ()->installEventFilter (&myWatcher);//安装全局的事件过滤器
    MyEvent myEvent(MyEventType); //产生事件
    mySender.sendEvent(&myArmy, &myEvent);  //发送事件,事件，栈上建立
    mySender.postEvent (&myArmy, new MyEvent(MyEventType));//事件，对上建立
    return mySender.exec();  
} 
