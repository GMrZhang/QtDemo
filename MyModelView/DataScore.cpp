#include "DataScore.h"
DataScore::DataScore(QObject *parent) : QObject(parent)
{
    m_id = "NULL";
    m_name = "NULL";
    m_score = -1;
}

DataScore::DataScore(QString id, QString name, int score, QObject *parent)
{
    m_id = id;
    m_name = name;
    m_score = score;
}
DataScore::DataScore(const DataScore& another)
{
    m_id = another.m_id;
    m_name = another.m_name;
    m_score = another.m_score;
}

DataScore& DataScore::operator=(const DataScore& another)
{
    if(this != &another)
    {
        m_id = another.m_id;
        m_name = another.m_name;
        m_score = another.m_score;
    }
    return *this;
}

QString DataScore::id() const
{
    return m_id;
}
QString DataScore::name() const
{
    return m_name;
}
int DataScore::score() const
{
    return m_score;
}
