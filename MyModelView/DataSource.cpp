#include "DataSource.h"
#include <QFile>
#include <QTextStream>
#include <QStringList> 
DataSource::DataSource(QObject *parent) : QObject(parent)
{

} 
bool DataSource::parse(QString line, DataScore& info)
{    
	bool ret = true;    
//    注意下面的逗号，要区分中文和英文的逗号
    QStringList list = line.split("，", QString::SkipEmptyParts);
	if(list.count() == 3)    
	{        
		QString id = list[0].trimmed();        
		QString name = list[1].trimmed();        
		QString score = list[2].trimmed();        
		int value = score.toInt(&ret);        
		if(ret && (0 <= value) && (value <= 100))        
		{            
			info = DataScore(id, name, value);        
		}        
		else        
		{            
			ret = false;        
		}    
	}    
	else    
	{        
		ret = false;   
	}    
	return ret;
} 
bool DataSource::setDataSource(const QString source)
{    
	bool ret = true;    
	QFile file(source);    
	if(file.open(QFile::ReadOnly | QFile::Text))    
	{        
		QTextStream in(&file);        
		while(!in.atEnd())        
		{            
			DataScore score;            
			if(parse(in.readLine(), score))           
			{                
				m_data.append(score);            
			}        
		}        
		file.close();    
	}    
	else    
	{        
		ret = false;   
	}     
	return ret;
} 

QList<DataScore> DataSource::fetchData()
{    
	QList<DataScore> ret = m_data;    
    m_data.clear();
    return ret;
} 

int DataSource::count() const
{    
	return m_data.count();
}
