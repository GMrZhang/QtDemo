#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QtQuick>
#include <QQuickView>
#include "ColorMaker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");
    QQuickView *view = new QQuickView;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view->show();

    return app.exec();
}
