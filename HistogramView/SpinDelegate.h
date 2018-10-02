#ifndef SPINDELEGATE_H
#define SPINDELEGATE_H
 
#include <QItemDelegate>
 
class SpinDelegate : public QItemDelegate
{
public:
    SpinDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
 
#endif // SPINDELEGATE_H