#include "ThreadFromQObject.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Controller * ctrl = new Controller();
    for( int num = 0; num < 126; num++ )
    {
        QString str = QString("%1").arg(num);
        ctrl->testEmitSignal ( str );
    }
    return app.exec ();
}
