#include "ProgramLanguageModel.h"
#include <QDebug>

ProgramLanguageModel::ProgramLanguageModel( QObject * parent ):QAbstractTableModel (parent)
{
    mMapLanguageRatio.insert ("C++",50);
    mMapLanguageRatio.insert ("Python",30);
    mMapLanguageRatio.insert ("Java",20);
}

int ProgramLanguageModel::rowCount(const QModelIndex &parent) const
{
    return mMapLanguageRatio.count();
}

int ProgramLanguageModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ProgramLanguageModel::data(const QModelIndex &index, int role) const
{
//    qDebug()<<"data"<<index.column ()<<index.row ();
    if(!index.isValid ())
    {
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole )
    {
        return int(Qt::AlignCenter | Qt::AlignLeft );
    }
    if( role == Qt::DisplayRole && index.column () == 0 )
    {
        return mMapLanguageRatio.keys()[index.row()];
    }
    if( role == Qt::DisplayRole && index.column () == 1 )
    {
        return mMapLanguageRatio.values()[index.row()];
    }
    return QVariant();
}

Qt::ItemFlags ProgramLanguageModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags( index )| Qt::ItemIsEditable;
}

bool ProgramLanguageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }
    return true;
}
