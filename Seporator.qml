import QtQuick 2.15

Rectangle{

    property string sizeSep: "empty"
    property real cstWidth: 1

//    width: parent.width


//    anchors.left: parent.left
//    anchors.right: parent.right
    width: 10
    height: 1
    color: "black"

    Rectangle{
        width: parent.cstWidth + 5
        height: 1
        color: "black"
    }

//    z: 1

    Text{
        anchors.right: parent.left
        anchors.bottom: parent.top
        text: parent.sizeSep
    }
}
