#include "DateDelegate.h"
#include <QDateTimeEdit>
 
DateDelegate::DateDelegate(QObject* parent):QItemDelegate(parent)
{
 
}
 
QWidget* DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* ret = NULL;
    if(index.data().type() == QVariant::String)
    {
        QDateTimeEdit* date = new QDateTimeEdit(parent);
        date->setDisplayFormat("yyyy-MM-dd");
        date->setCalendarPopup(true);
        ret = date;
    }
    else
    {
        ret = QItemDelegate::createEditor(parent, option, index);
    }
    return ret;
}
 
void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
 
void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::String)
    {
        QString datestr = index.data().toString();
        QDate date = QDate::fromString(datestr, Qt::ISODate);
        QDateTimeEdit* edit = dynamic_cast<QDateTimeEdit*>(editor);
        edit->setDate(date);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}
 
void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::String)
    {
        QDateTimeEdit* edit = dynamic_cast<QDateTimeEdit*>(editor);
        QDate date = edit->date();
        model->setData(index, QVariant(date.toString(Qt::ISODate)));
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}