#include "DataModel.h"
#include <QStandardItem>
#include <QVariant> 

DataModel::DataModel(QObject *parent) : QObject(parent)
{

}

bool DataModel::add(const DataScore info)
{    
    bool ret = true;
    QStandardItem* root = m_model.invisibleRootItem();
	QStandardItem* id = new QStandardItem();    
	QStandardItem* name = new QStandardItem();    
	QStandardItem* score = new QStandardItem();     
	if( m_model.rowCount() > 0 )    
	{        
		QStringList list;        
		list.append("ID");        
		list.append("Name");        
		list.append("Score");        
		m_model.setHorizontalHeaderLabels(list);    
	}    
	if( (root != NULL) && (id != NULL) && (name != NULL) && (score != NULL) )    
	{        
		id->setData(info.id(), Qt::DisplayRole);        
		name->setData(info.name(), Qt::DisplayRole);        
		score->setData(info.score(), Qt::DisplayRole);         
		id->setEditable(false);        
		name->setEditable(false);        
		score->setEditable(false);         
		int currentRow = count();         
		root->setChild(currentRow, 0, id);        
		root->setChild(currentRow, 1, name);        
		root->setChild(currentRow, 2, score);   
   }   
   else    
   {       
   		ret = false;   
   }    
   return ret;
} 

bool DataModel::add(const QList<DataScore> list)
{    
	bool ret = true;    
	for(int i = 0; i < list.count(); i++)   
	{        
		ret = ret && add(list[i]);    
	}   
	return ret;
} 

bool DataModel::remove(const int index)
{    
	bool ret = true;    
	if((0 <= index) && (index <= count()))   
	{        
		m_model.removeRow(index);    
	}    
	else   
	{        
		ret = false;    
	}    
	return ret;
} 

DataScore DataModel::getRecord(const int row) const
{    
	DataScore ret;    
	if((0 <= row) && (row <= count()))   
	{        
		QModelIndex index0 = m_model.index(row, 0, QModelIndex());        
		QModelIndex index1 = m_model.index(row, 1, QModelIndex());        
		QModelIndex index2 = m_model.index(row, 2, QModelIndex());        
		QVariant v0 = index0.data();        
		QVariant v1 = index1.data();      
		QVariant v2 = index2.data();        
		ret = DataScore(v0.toString(), v1.toString(), v2.toInt());    
	}    
	return ret;
} 

int DataModel::count() const
{    
	return m_model.rowCount();
} 

void DataModel::setView(QTableView& view)
{    
	view.setModel(&m_model);
} 

void DataModel::clear()
{    
	m_model.clear();
}
