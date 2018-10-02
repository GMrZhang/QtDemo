#ifndef DATASCORE_H
#define DATASCORE_H
#include <QObject>
#include <QString>

class DataScore : public QObject
{
    Q_OBJECT

    private:
        QString m_id;
        QString m_name;
        int m_score;

    public:
        explicit DataScore(QObject *parent = 0);
        DataScore(QString id, QString name, int score, QObject *parent = 0);
        DataScore(const DataScore& another);
        DataScore& operator=(const DataScore& another);
        QString id() const;    QString name() const;    int score() const;
};

#endif // DATASCORE_H

