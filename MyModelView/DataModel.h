#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QObject>
#include <QStandardItem>
#include <QTableView>
#include "DataScore.h"
class DataModel : public QObject
{
    Q_OBJECT

        QStandardItemModel m_model;

    public:
        explicit DataModel(QObject *parent = 0);
        bool add(const DataScore info);
        bool add(const QList<DataScore> list);
        bool remove(const int index);
        DataScore getRecord(const int row) const;
        int count() const;
        void setView(QTableView& view);
        void clear();
};
#endif // DATAMODEL_H
