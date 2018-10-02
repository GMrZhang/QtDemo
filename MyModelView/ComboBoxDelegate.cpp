#include "ComboBoxDelegate.h"
#include <QComboBox> 
#include <QDebug>

ComboBoxDelegate::ComboBoxDelegate(QObject* parent):QItemDelegate(parent)
{

}

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{    
    qDebug()<<"createEditor"<< index.data().type ();
    QWidget* ret = NULL;
    if(index.data().type() == QVariant::String)
    {
        QComboBox *combo = new QComboBox(parent);
        if(combo != NULL)
        {   //在下拉框中增加选项
            combo->addItem("C");
            combo->addItem("C++");
            combo->addItem("Java");
            combo->addItem("Python");
        }
        ret = combo;
    }
    else
    {
        ret = QItemDelegate::createEditor(parent, option, index);
    }
    return ret;
}
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::String)
    {
        QComboBox *combo = dynamic_cast<QComboBox*>(editor);
        if(combo != NULL)
        {
            for(int i = 0; i < combo->count(); i++)
            {
                if(combo->itemText(i) == index.data().toString())
                {
                    combo->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);


    }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::String)
    {
        QComboBox* combo = dynamic_cast<QComboBox*>(editor);
        if(combo != NULL)
        {
            model->setData(index, combo->currentText(), Qt::DisplayRole);
        }
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}


