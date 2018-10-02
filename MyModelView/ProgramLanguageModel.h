#ifndef PROGRAMLANGUAGEMODEL_H
#define PROGRAMLANGUAGEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QMap>
#include <QString>

class ProgramLanguageModel : public QAbstractTableModel
{
public:
    ProgramLanguageModel( QObject * parent = 0 );
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
private:
    QMap<QString,int> mMapLanguageRatio;
};

#endif // PROGRAMLANGUAGEMODEL_H
