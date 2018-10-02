#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QList>
#include "DataScore.h"
class DataSource : public QObject
{
    Q_OBJECT
    private:
        QList<DataScore> m_data;
        bool parse(QString line, DataScore& info);

    public:
        explicit DataSource(QObject* parent = 0);
        bool setDataSource(const QString source);
        QList<DataScore> fetchData();
        int count() const;
};

#endif
// DATASOURCE_H

