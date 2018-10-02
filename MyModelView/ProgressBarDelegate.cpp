#include "ProgressBarDelegate.h"
#include <QApplication>
#include <QEvent>

ProgressBarDelegate::ProgressBarDelegate(QObject* parent):QItemDelegate(parent)
{
}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::Int)
    {
        const int delta = 4;
        int progress = index.data().toInt();
        QStyleOptionProgressBar progressBarOption;
        int top = option.rect.top() + delta;
        int left = option.rect.left() + delta;
        int width = option.rect.width() - 2*delta;
        int height = option.rect.height() - 2*delta;

        progressBarOption.rect = QRect(left, top, width, height);
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = progress;
        progressBarOption.textVisible = true;
        progressBarOption.text = QString().sprintf("%d", progress) + "%";
        progressBarOption.textAlignment = Qt::AlignCenter;
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

bool ProgressBarDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    bool ret = true;
    if(event->type() != QEvent::MouseButtonDblClick)
    {
        QItemDelegate::editorEvent(event, model, option, index);
    }
    return ret;
}
