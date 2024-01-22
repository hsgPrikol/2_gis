import QtQuick 2.15

Rectangle{

    property string sizeSep: "empty"

//    width: parent.width


//    anchors.left: parent.left
//    anchors.right: parent.right
    width: 10
    height: 1
    color: "black"

//    z: 1

    Text{
        anchors.right: parent.left
        anchors.bottom: parent.top
        text: parent.sizeSep
    }


    Component.onCompleted: {
        console.log(parent.width)
    }
}
