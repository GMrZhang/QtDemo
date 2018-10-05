#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    //鼠标事件
    void mousePressEvent(QMouseEvent *event );
    //键盘事件
    void keyPressEvent(QKeyEvent * event);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
