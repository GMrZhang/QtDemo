#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H 
#include <QItemDelegate> 
class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject* parent = 0);
    //创建编辑器
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //更新编辑器大小
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //通过索引从模型中获取数据并设置到编辑器
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //将编辑后的数据写入模型
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

}; 
#endif
// COMBOBOXDELEGATE_H
