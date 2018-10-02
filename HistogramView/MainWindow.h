#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QStandardItemModel>
#include "DateDelegate.h"
#include "ComboBoxDelegate.h"
#include "SpinDelegate.h"
#include "HistogramView.h"
#include <QTableView>
#include <QFile>
#include <QSplitter>
#include <QTableView>
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
private:
    DateDelegate *datedelegate;
    ComboBoxDelegate *comboboxdelegate;
    SpinDelegate *spindelegate;
    QStandardItemModel *model;
    QTableView *tableview;
    HistogramView *histogramview;
    QTableView *currencyview;
};
 
#endif // MAINWINDOW_H