#include "HistogramView.h"
#include <QMouseEvent>
#include <QPainter>
 
HistogramView::HistogramView(QWidget *parent):QAbstractItemView(parent)
{}
 
void HistogramView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);
 
    viewport()->update();
}
 
QRect HistogramView::visualRect(const QModelIndex &index) const
{
 
}
 
void HistogramView::scrollTo(const QModelIndex &index, ScrollHint hint)
{}
 
QModelIndex HistogramView::indexAt(const QPoint &point) const
{
    QPoint newPoint(point.x(),point.y());
 
    QRegion region;
    foreach(region,listRegionM)
    {
        if (region.contains(newPoint))
        {
            int row = listRegionM.indexOf(region);
            QModelIndex index = model()->index(row, 3,rootIndex());
            return index;
        }
    }
 
    return QModelIndex();
}
 
QModelIndex HistogramView::moveCursor(QAbstractItemView::CursorAction cursorAction,Qt::KeyboardModifiers modifiers)
{}
 
int HistogramView::horizontalOffset() const
{
}
 
int HistogramView::verticalOffset() const
{}
 
bool HistogramView::isIndexHidden(const QModelIndex &index) const
{}
 
void HistogramView::setSelectionModel(QItemSelectionModel * selectionModel)
{
    selections = selectionModel;
}
 
void HistogramView::mousePressEvent(QMouseEvent *e)
{
    QAbstractItemView::mousePressEvent(e);
    setSelection(QRect(e->pos().x(),e->pos().y(),1,1),QItemSelectionModel::SelectCurrent);
}
 
QRegion HistogramView::itemRegion(QModelIndex index)
{
    QRegion region;
 
    if (index.column() == 3)
        region = listRegionM[index.row()];
 
    return region;
}
 
void HistogramView::setSelection ( const QRect &rect, QItemSelectionModel::SelectionFlags flags )
{
     int rows = model()->rowCount(rootIndex());
     int columns = model()->columnCount(rootIndex());
     QModelIndex selectedIndex;
 
     for (int row = 0; row < rows; ++row)
     {
         for (int column = 1; column < columns; ++column)
         {
             QModelIndex index = model()->index(row, column, rootIndex());
             QRegion region = itemRegion(index);
 
             if (!region.intersected(rect).isEmpty())
             selectedIndex = index;
         }
     }
 
     if(selectedIndex.isValid())
         selections->select(selectedIndex,flags);
     else
     {
         QModelIndex noIndex;
         selections->select(noIndex, flags);
     }
}
 
QRegion HistogramView::visualRegionForSelection(const QItemSelection &selection) const
{}
 
void HistogramView::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected )
{
    viewport()->update();
}
 
void HistogramView::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
 
    painter.setPen(Qt::black);
    int x0 = 40;
    int y0 = 250;
 
    // draw coordinate
    painter.drawLine(x0, y0, 40, 30);
    painter.drawLine(38, 32, 40, 30);
    painter.drawLine(40, 30, 42, 32);
    painter.drawText(5, 45, tr("income"));
 
    for (int i=1; i<5; i++) {
        painter.drawLine(-1,-i*50,1,-i*50);
        painter.drawText(-20,-i*50,tr("%1").arg(i*5));
    }
 
    // x轴
    painter.drawLine(x0, y0, 540, 250);
    painter.drawLine(538, 248, 540, 250);
    painter.drawLine(540, 250, 538, 252);
    painter.drawText(500, 270, tr("name"));
    int row;
    // name
    int posD = x0+20;
    for (row = 0; row < model()->rowCount(rootIndex()); row++)
    {
        QModelIndex index = model()->index(row, 0, rootIndex());
        QString dep = model()->data(index).toString();
 
        painter.drawText(posD,y0+20,dep);
        posD += 50;
    }
    // income
    int posM = x0+20;
    for (row = 0; row < model()->rowCount(rootIndex()); row++)
    {
        QModelIndex index = model()->index(row, 3, rootIndex());
        int income = model()->data(index).toDouble();
 
        int width = 10;
 
        if (selections->isSelected(index))
            painter.setBrush(QBrush(Qt::darkBlue,Qt::SolidPattern));
        else
            painter.setBrush(Qt::blue);
 
        painter.drawRect(QRectF(posM + 10, y0-income/25, width, income/25));
        QRegion regionM(posM + 10, y0-income/25, width, income/25);
        listRegionM << regionM;
 
        posM += 50;
    }
}