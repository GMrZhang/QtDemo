#include <QCoreApplication>
#include "ReflectionObject.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReflectionObject theObject;
    const QMetaObject*theMetaObject =theObject.metaObject();

    int metathodCount = theMetaObject->methodCount();
    for( int metathodIndex = 0; metathodIndex < metathodCount; ++metathodIndex)
    {
        QMetaMethod oneMethod = theMetaObject->method(metathodIndex);
        qDebug() <<"typeName: " <<oneMethod.typeName();
        qDebug() <<"signature: " <<oneMethod.methodSignature().data();
        qDebug() <<"methodType: " <<oneMethod.methodType();;
        qDebug() <<"parameterNames: " <<oneMethod.parameterNames() <<"\n";
    }

    /*遍历该类的属性: */
    int propertyCount = theMetaObject->propertyCount();
    for(int propertyIndex = 0; propertyIndex < propertyCount; ++propertyIndex)
    {
        QMetaProperty oneProperty =theMetaObject->property(propertyIndex);
        qDebug() <<"name: " << oneProperty.name();
        qDebug() <<"type: " << oneProperty.type() <<"\n";
    }

    /*遍历该类的枚举集合*/
    int enumeratorCount = theMetaObject->enumeratorCount();//返回类里枚举的个数
    for( int enumeratorIndex = 0; enumeratorIndex < enumeratorCount; ++enumeratorIndex)
    {
        QMetaEnum oneEnumerator = theMetaObject->enumerator(enumeratorIndex);

        int enumCount = oneEnumerator.keyCount();
        for(int enumIndex = 0;enumIndex < enumCount; ++enumIndex)
        {
             qDebug() <<oneEnumerator.key(enumIndex) <<" ==> " <<oneEnumerator.value(enumIndex);
        }
    }

    using namespace std;
    //3.使用反射
    cout << "-------test property-----------" << "\n";
    ReflectionObject newObj;
    newObj.setProperty("m_Id", 66);
    cout << newObj.property( "m_Id" ).toString().toStdString() << "\n";
    cout << newObj.Id() << "\n";
    cout << "--------end----------" << "\n";

    // 4.invokeMethod
    int ret;
    ReflectionObject newObj2;
    newObj2.setId( 20 );
    newObj2.setId( 50 );
    QMetaObject::invokeMethod( &newObj2, "testInvokableFunc", Qt::DirectConnection,   Q_RETURN_ARG(int, ret ), Q_ARG(QString, "+"));
    cout << ret << endl;
    return a.exec();
}
