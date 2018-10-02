#include "DataAppUI.h"
#include "DataModel.h"
#include "DataScore.h"
#include "DataSource.h"
#include <QEvent>
#include <QMessageBox>
DataAppUI::DataAppUI(QWidget *parent):QWidget(parent)
{
	m_view.setParent(this);    
	m_view.move(10, 10);    
	m_view.resize(300, 200);
	m_view.installEventFilter(this);
	m_refresh.setParent(this);
	m_refresh.move(10, 220);    
	m_refresh.resize(80, 30);
	m_refresh.setText("Refresh");
	m_clear.setParent(this);    
	m_clear.move(100, 220);    
	m_clear.resize(80,30);    
	m_clear.setText("Clear");
	m_score.setParent(this);    
	m_score.move(190, 220);    
	m_score.resize(80, 30);
	m_score.setText("Score");     
	m_menu.addAction("Delete");
	m_model.setView(m_view);     
	connect(&m_refresh, SIGNAL(clicked()), this,SLOT(onRefresh()));    
	connect(&m_clear, SIGNAL(clicked()), this,SLOT(onClear()));    
	connect(&m_score, SIGNAL(clicked()), this,SLOT(onScore()));    
    connect(m_menu.actions()[0], SIGNAL(triggered()), this,	SLOT(onDelete()));
    onRefresh();
}
void DataAppUI::onRefresh()
{
    DataSource source;
    m_model.clear();
    if(source.setDataSource("E:/QT/Project/MyModelView/DataSource.txt"))
    {
        m_model.add(source.fetchData());
    }
    else
    {
        QMessageBox::critical(this, "Data Source Error", "Set Data Source Error",QMessageBox::Ok);
    }
}

void DataAppUI::onClear()
{
    m_model.clear();
}

void DataAppUI::onScore()
{
    int min = 256;
    int max = 0;
    int average = 0;
    if( m_model.count() > 0 )
    {
        for(int i=0; i<m_model.count(); i++)
        {
            DataScore info = m_model.getRecord(i);
            if( info.score()< min )
            {
                min = info.score();
            }
            if( info.score() > max )
            {
                max = info.score();
            }
            average += info.score();
        }
        average /=	m_model.count();
        QMessageBox::information(this, "Statistic",QString().sprintf("Min: %d\nMax: %d\nAverage: %d", min, max, average),QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this,	"Statistic", "No data record!", QMessageBox::Ok);
    }
} 

void DataAppUI::onDelete()
{
    m_model.remove(m_view.currentIndex().row());
}

bool DataAppUI::eventFilter(QObject *watched, QEvent *event)
{
    if((watched ==&m_view) && (event->type() == QEvent::ContextMenu))
    {
        m_menu.exec(cursor().pos());//在光标当前位置打开右键菜单
    }
    return QWidget::eventFilter(watched, event);
}

DataAppUI::~DataAppUI()
{
}
