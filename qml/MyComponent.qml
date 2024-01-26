import QtQuick 2.15
//import QtCharts 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

import Model.org 1.0

import "Colors.js" as Colors

Button {
    property color colorBackgraound: "#ede2d8"

    width: parent.width / 3 - 10
    height: parent.height
    onClicked: {
        _wsModel.startProcessing("/home/ibabushkin/Documents/Project_qt/t.txt")
    }

    background: Rectangle {
        color: "#303030"
        height: parent.height
        radius: 5
    }

    contentItem: Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: parent.text

        color: parent.colorBackgraound
        font.pixelSize: 16
    }
}
