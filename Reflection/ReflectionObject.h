#ifndef REFLECTIONOBJECT_H
#define REFLECTIONOBJECT_H

#include <QObject>
#include <QString>
#include <QMetaProperty>
#include <QMetaObject>
#include <QMetaMethod>
#include <iostream>

class ReflectionObject:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int Id READ Id WRITE setId)
    Q_PROPERTY( QString Name READ Name WRITE setName)
    Q_PROPERTY( QString Address READ Address WRITE setAddress)
    Q_PROPERTY( PriorityType Level READ Priority WRITE setPriority)

    Q_ENUMS( PriorityType )

public:
    enum PriorityType { High, Low, VeryHigh,VeryLow };

    Q_INVOKABLE int Id() {return m_Id; }
    Q_INVOKABLE QString Name() { return m_Name; }
    Q_INVOKABLE QString Address() { return m_Address; }
    Q_INVOKABLE PriorityType Priority() const {return m_Priority; }

    Q_INVOKABLE void setId(const int& id) { m_Id = id; }
    Q_INVOKABLE void setName(const QString& name) { m_Name = name; }
    Q_INVOKABLE void setAddress(const QString& address) { m_Address = address; }
    Q_INVOKABLE void setPriority(PriorityType priority) { m_Priority = priority; }

    Q_INVOKABLE int testInvokableFunc( QString flag )
    {
        std::cout << "hello" << std::endl;
        if ("+" == flag)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }




private:
    int      m_Id;
    QString  m_Name;
    QString  m_Address;

    PriorityType m_Priority;
};


#endif // REFLECTIONOBJECT_H
