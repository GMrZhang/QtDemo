#ifndef DATAAPPUI_H
#define DATAAPPUI_H
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QMenu>
#include "DataModel.h"
class DataAppUI : public QWidget
{
    Q_OBJECT
    private:
        DataModel m_model;
        QTableView m_view;
        QPushButton m_refresh;
        QPushButton m_clear;
        QPushButton m_score;
        QMenu m_menu;

    private slots:
        void onRefresh();
        void onClear();
        void onScore();
        void onDelete();

    public:
        DataAppUI(QWidget *parent = 0);
        bool eventFilter(QObject *watched, QEvent *event);
        ~DataAppUI();
};
#endif // DATAAPPUI_H
