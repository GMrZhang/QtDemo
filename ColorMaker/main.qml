import QtQuick 2.0
import QtQuick.Controls 1.1
import an.qt.ColorMaker 1.0  /*C++类*/

Rectangle {
    width: 360;
    height: 360;
    Text {
        id: timeLabel;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        font.pixelSize: 26;
    }
    ColorMaker {          /*ColorMaker 实例*/
        id: colorMaker;
        color: Qt.green;
    }

    Rectangle {
        id: colorRect;
        anchors.centerIn: parent;
        width: 200;
        height: 200;
        color: "blue";
    }

    Button {
        id: start;
        text: "start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            colorMaker.start(); /*调用ColorMaker类的槽函数*/
        }
    }
    Button {
        id: stop;
        text: "stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            colorMaker.stop(); /*调用ColorMaker类的槽函数*/
        }
    }

    function changeAlgorithm(button, algorithm){
        switch(algorithm)
        {
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomRed";
            break;
        case 2:
            button.text = "RandomGreen";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button {
        id: colorAlgorithm;
        text: "RandomRGB";
        anchors.left: stop.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            var algorithm = (colorMaker.algorithm() + 1) % 5;
            changeAlgorithm(colorAlgorithm, algorithm);
            colorMaker.setAlgorithm(algorithm); /*调用ColorMaker的函数*/
        }
    }

    Button {
        id: quit;
        text: "quit";
        anchors.left: colorAlgorithm.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        colorMaker.color = Qt.rgba(0,180,120, 255);
        colorMaker.setAlgorithm(ColorMaker.LinearIncrease);/*调用ColorMaker的枚举变量*/
        changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
    }

    Connections {
        target: colorMaker;
        onCurrentTime:{ /*使用ColorMaker类的信号CurrentTime(const QString &strTime)*/
            timeLabel.text = strTime;
            timeLabel.color = colorMaker.timeColor;
        }
    }

    Connections {
        target: colorMaker; /*使用ColorMaker类的信号ColorChanged()*/
        onColorChanged:{
            colorRect.color = color;
        }
    }
}
