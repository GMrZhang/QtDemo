#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QItemDelegate>

class ProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ProgressBarDelegate(QObject* parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // PROGRESSBARDELEGATE_H
