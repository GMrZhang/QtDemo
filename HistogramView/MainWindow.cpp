#include "MainWindow.h"
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
 
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
    model = new QStandardItemModel(4, 4, this);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Name"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Birthday"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Job"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Income"));
 
    tableview = new QTableView(this);
    tableview->setModel(model);
    datedelegate = new DateDelegate(this);
    comboboxdelegate = new ComboBoxDelegate(this);
    spindelegate = new SpinDelegate(this);
    tableview->setItemDelegateForColumn(1, datedelegate);
    tableview->setItemDelegateForColumn(2, comboboxdelegate);
    tableview->setItemDelegateForColumn(3, spindelegate);
 
    histogramview = new HistogramView(this);
    histogramview->setModel(model);
 
    QFile file("E:/QT/Project/HistogramView/data.tab");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
         QTextStream stream(&file);
         QString line;
 
         model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());
         int row = 0;
         do
         {
             line = stream.readLine();
             if (!line.isEmpty())
             {
                 model->insertRows(row, 1, QModelIndex());
                 QStringList pieces = line.split(",", QString::SkipEmptyParts);
                 model->setData(model->index(row, 0, QModelIndex()),pieces.value(0));
                 model->setData(model->index(row, 1, QModelIndex()),pieces.value(1));
                 model->setData(model->index(row, 2, QModelIndex()),pieces.value(2));
                 model->setData(model->index(row, 3, QModelIndex()),pieces.value(3));
                 row++;
             }
         } while (!line.isEmpty());
         file.close();
    }
    else
    {
        QMessageBox::critical(this, "open file error", "open file error",QMessageBox::Ok);
    }
 
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    tableview->setSelectionModel(selectionModel);
    histogramview->setSelectionModel(selectionModel);
 
    connect(selectionModel,SIGNAL(selectionChanged(const QItemSelection, const QItemSelection)),
            histogramview,SLOT(selectionChanged(const QItemSelection, const QItemSelection)));
    connect(selectionModel,SIGNAL(selectionChanged(const QItemSelection, const QItemSelection)),
            tableview,SLOT(selectionChanged(const QItemSelection, const QItemSelection)));
 
     QSplitter *splitter = new QSplitter(this);
     splitter->setOrientation(Qt::Vertical);
 
     tableview->setMaximumHeight(150);
     histogramview->setMaximumHeight(300);
     splitter->addWidget(tableview);
     splitter->addWidget(histogramview);
     setCentralWidget(splitter);
     setWindowTitle(tr("table View"));
     setMinimumSize(600, 480);
}
