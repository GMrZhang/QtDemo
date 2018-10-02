#include <QApplication>
#include "CurrencyModel.h"
#include <QTableView>
#include <QMap>
#include "DataAppUi.h"
#include "ProgramLanguageModel.h"
#include "ProgressBarDelegate.h"
#include "ComboBoxDelegate.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

//只读模型测试
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QMap<QString, double> data;
//    data["USD"] = 1.0000;
//    data["CNY"] = 0.1628;
//    data["GBP"] = 1.5361;
//    data["EUR"] = 1.2992;
//    data["HKD"] = 0.1289;
//    QTableView view;
//    CurrencyModel *model = new CurrencyModel(&view);
//    model->setCurrencyMap(data);
//    view.setModel(model);
//    view.resize(400, 300);
//    view.show();
//    return a.exec();
//}

////自定模型测试
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    DataAppUI appUI;
//    appUI.show();
//    return app.exec();
//}

//ProgressBarDelegate 测试
//int main( int argc, char *argv[])
//{
//    QApplication app(argc,argv);

//    QTableView  * tableView =  new QTableView();
//    ProgressBarDelegate * delegate = new ProgressBarDelegate();
//    ProgramLanguageModel * model = new ProgramLanguageModel(tableView);
//    tableView->setModel (model);
//    tableView->setItemDelegateForColumn (1, delegate);
//    tableView->show();
//    return app.exec();
//}

//ComboBoxDelegate 测试
//int main(int argc,char *argv[])
//{
//    QApplication app(argc,argv);
//    QTableView tableView;
//    ComboBoxDelegate *delegate = new ComboBoxDelegate();
//    ProgramLanguageModel *model = new ProgramLanguageModel(&tableView);
//    tableView.setModel ( model);
//    qDebug()<<delegate;
////    tableView.setItemDelegate (delegate);
//    tableView.setItemDelegateForColumn (0, delegate);
//    qDebug()<<tableView.itemDelegateForColumn (0);
//    tableView.show();
//    return app.exec();
//}

//ComboBoxDelegate 测试
int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    QTableView tableView;
    ComboBoxDelegate *delegate = new ComboBoxDelegate();
    QStandardItemModel *model = new QStandardItemModel(3,2);
    model->setItem(1,0,new QStandardItem("C++"));
    model->setItem(2,0,new QStandardItem("C++"));
    model->setItem(3,0,new QStandardItem("C++"));
    tableView.setModel ( model);
    tableView.setItemDelegateForColumn (0, delegate);
    tableView.show();
    return app.exec();
}
