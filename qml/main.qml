import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

import Model.org 1.0

import "../js/Colors.js" as Colors

ApplicationWindow {
    id: rootId
    width: 1280
    height: 720

    title: "2Гистограмм"

    visible: true

    LinearGradient{
        anchors.fill: parent
        start: Qt.point(0,0)
        end: Qt.point(width, height)
        gradient: Gradient {

            GradientStop {
                position: 0.0
                color: "#1c2e2c"
            }
            GradientStop {
                position: 0.1
                color: "#171617"
            }
            GradientStop {
                position: 0.5
                color: "#171717"
            }
            GradientStop {
                position: 1.0
                color: "#1c2e2c"
            }
        }
    }



    Row {
        id: iconTextId
        height: 140
        width: 300
        z: 1
        anchors.left: parent.left
        anchors.margins: 30

        spacing: 15

        Image {
            id: imgId
            anchors.bottom: parent.bottom
            //            height: parent
            antialiasing: true
            width: 150; height: 100
            source: "qrc:/images/images/logo_2.png"
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            antialiasing: true
            width: 5
            height: 80
            radius: 2

            color: "#616161"
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text: "Гистограмма"
            color: "#616161"
            font.pixelSize: 22


        }
    }

    FileDialog{
        id: fileDialogId
        title: "Выберете файл"
        nameFilters: ["Text files (*.txt)", "HTML files (*.html *.htm)"]

        onAccepted: {

            if (fileDialogId.fileUrl !== "") {
                _wsModel.startProcessing(fileDialogId.fileUrl);
            } else {
                console.log("mistake");
            }
        }

        onRejected: {
            console.log(fileUrl)
        }
    }

    FileDialog {
        id:  saveFileDialogId
        title: "Save File"
        selectExisting: false
        selectFolder: false
        nameFilters: ["CSV Files (*.csv)"]

        onAccepted: {

            var chosenFile = saveFileDialogId.fileUrl.toString().replace("file:///", "");
            if (chosenFile !== "") {
                console.log("Selected file path:", chosenFile);
            } else {
                console.log("File selection canceled.");
            }
        }
        onRejected: {
            console.log("File selection canceled.");
        }
    }

    Row{
        id: rowInfoId
        height: 70

        anchors.top: iconTextId.bottom
        anchors.right: parent.right
        //        anchors.bottom: parent.bottom
        anchors.margins: 40
        width: parent.width / 5 * 3.5
        spacing: 10

        Rectangle {
            id: lableFileInfoId
            color: "#252525"
            width: parent.width / 2 - 10
            height: 70

            border.width: 1
            border.color: Colors.border()

            radius: 5

            Label {
                anchors.top: parent.right
                anchors.left: parent.left
                anchors.margins: 5

                background: Rectangle {
                    color: "transparent"

                    Text {
                        text: "Название файла"
                        //                        anchors.centerIn: parent
                        color: "#17a81a"
                    }
                }
            }

            Label {
                anchors.top: parent.right
                anchors.left: parent.left
                anchors.margins: 5

                background: Rectangle {
                    color: "transparent"

                    Text {
                        text: ""
                        //                        anchors.centerIn: parent
                        //                        color: "#"
                    }
                }
            }

        }

        Rectangle {
            //            id: progressBarId
            color: "#252525"
            width: parent.width / 2
            height: 70

            border.width: 1
            border.color: Colors.border()
            radius: 5

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: progressBarId.top
                anchors.bottomMargin: 5
                text: _wsModel.viewManager.processValue + "%"
                background: Rectangle{
                    color: "transparent"

                    //                    border.width: 1
                    //                    border.color: "red"
                }

                color: "white"
                font.pixelSize: 22

            }

            ProgressBar{
                id: progressBarId
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                from: 0
                //                height: 50
                to: 100
                value: _wsModel.viewManager.processValue

                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 6
                    color: "#e6e6e6"
                    radius: 3
                }

                contentItem: Item {
                    implicitWidth: 200
                    implicitHeight: 4

                    Rectangle {
                        width: progressBarId.visualPosition * parent.width
                        height: parent.height
                        radius: 2
                        color: "#17a81a"
                    }
                }
            }

        }
    }

    Rectangle{
        id: controllerId

        anchors.top: rowInfoId.top
        anchors.right: lwBackId.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 40
        anchors.topMargin: 0
        anchors.rightMargin: 50

        border.width: 1
        border.color: Colors.border()
        radius: 5

        color: "transparent"

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Row {
                spacing: 10
                height: 50
                width: parent.width
                CustomButton {
                    text: "Open"

                    onClicked: {
                        fileDialogId.open();
                    }
                }
                CustomButton{
                    colorBackgraound: "#252525"
                }
                CustomButton {
                    width: parent.width / 3
                    text: "Save"

                    onClicked: {
                        saveFileDialogId.open()
                    }
                }
            }

            Row {
                spacing: 10
                height: 50
                width: parent.width
                CustomButton {
                    text: "A-Z"

                    onClicked: {

                    }
                }
                CustomButton {
                    text: ""
                    colorBackgraound: "#252525"

                }
                CustomButton {
                    width: parent.width / 3
                    text: "Z-A"

                }
            }

            Row {
                spacing: 10
                height: 50
                width: parent.width
                CustomButton {
                    text: "1-9"

                    onClicked: {
                    }
                }
                CustomButton {
                    colorBackgraound: "#252525"
                }
                CustomButton {
                    width: parent.width / 3
                    text: "9-1"


                }
            }
            CustomButton {
                text: "Clear"

                width: parent.width
                height: 50

                onClicked: {

                }
            }
            CustomButton {
                text: "Pause"

                width: parent.width
                height: 50
                colorBackgraound: "#17a81a"

                onClicked: {

                }
            }
        }
    }


    Rectangle{
        id: lwBackId
        z: 1
        //        anchors.centerIn: parent
        anchors.top: rowInfoId.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 40
        anchors.topMargin: 10

        width: parent.width / 5 * 3.5
        //        height: parent.height / 5 * 4 - 30

        color: "#191919"

        radius: 5

        border.width: 1
        border.color: Colors.border()
        property real tmpH: height / 5

        Column {
            anchors.fill: parent

            Repeater {
                id: axisXId
                anchors.fill: parent
//                model: 5
                model: 5

                delegate: Seporator {
                    //                    property real step: _wsModel.viewManager.maxReapeatedWord / 5

                    y: lwBackId.tmpH * model.index + 10
                    x: -5
                    sizeSep: Math.floor(_wsModel.viewManager.maxRepeatedWord - ((_wsModel.viewManager.maxRepeatedWord / 5) * model.index))
                    cstWidth: rootId.width / 5 * 3.5
                    height: 1
                    color: Colors.symbols()
                }
            }
        }

        ListView {
            id: lw

            anchors.fill: parent
            anchors.margins: 10
            anchors.bottomMargin: 30

            spacing: 10
            orientation: ListView.Horizontal
            interactive: false

            model: _wsModel.viewManager.proxyModel

            delegate: Rectangle {
                property real itemWidth: ((lwBackId.width) - (15 * 10 + 10)) / 15
                property real itemHeight: lwBackId.height / _wsModel.viewManager.maxRepeatedWord

                width: itemWidth
                height: itemHeight * model.count - 10
                y: lwBackId.height - (itemHeight * model.count)

                visible: model.index < 15

                border.width: 1
                //                color: "red"
                //                color: Qt.rgba(Math.random(), Math.random(), Math.random())
                color: Colors.gis_blue()

                Text {
                    height: 30
                    width: parent.width
                    text: model.count + ""
                    anchors.top: parent.top
                    anchors.topMargin: 15
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    height: 30
                    width: parent.width
                    text: model.word

                    color: Colors.symbols()
                    anchors.top: parent.bottom
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onClicked: console.log("Clicked!")

                    ToolTip {
                        visible: parent.containsMouse ? true : false
                        width: implicitWidth
                        height: implicitHeight
                        clip: true

                        background: Rectangle{
                            anchors.fill: parent

                            //                            color: "#2e0000"
                            color: "#343541"
                            opacity: 0.8

                            radius: 4
                        }
                        contentItem: Text{
                            anchors.centerIn: parent
                            text: "Значение " + model.count + "\n" + model.word + " поз. " + model.index
                            color: "#ffffff"
                        }

                    }
                }
            }
        }
    }
}
