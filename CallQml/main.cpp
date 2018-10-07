#include <QtGui/QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include "ChangeQmlColor.h"
#include <QMetaObject>
#include <QDebug>
#include <QColor>
#include <QVariant>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView * view = new QQuickView();
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view->show();

    QQuickItem * rootItem = view->rootObject();
    new ChangeQmlColor(rootItem);
    QObject * quitButton = rootItem->findChild<QObject*>("quitButton");
    if(quitButton)
    {
        QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    }

    QObject *textLabel = rootItem->findChild<QObject*>("textLabel");
    if(textLabel)
    {
        //1. failed call
        bool bRet = QMetaObject::invokeMethod(textLabel, "setText", Q_ARG(QString, "world hello"));
        qDebug() << "call setText return - " << bRet;
        textLabel->setProperty("color", QColor::fromRgb(255,0,0));
        bRet = QMetaObject::invokeMethod(textLabel, "doLayout");
        qDebug() << "call doLayout return - " << bRet;
    }

    return app.exec();
}
