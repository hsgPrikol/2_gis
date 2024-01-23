import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Model 1.0

ApplicationWindow {
    id: rootId
    width: 640
    height: 480

    title: "2Gis histogram"

    visible: true

    Md {
        id: md
    }

//    WordStatsModel {
//        id: wsModel


//    }

    Rectangle{
        id: lwBackId
        z: 1
        anchors.centerIn: parent

        width: parent.width / 5 * 4
        height: parent.height / 5 * 4 - 30

        border.width: 1

        property real tmpH: height / 5

        Column {
            anchors.fill: parent

            Repeater {
                anchors.fill: parent
                model: 5

                delegate: Seporator {
                    property real step: 100 / 5.

                    y: lwBackId.tmpH * model.index + 10
                    x: -5
                    sizeSep: 100 - (step * model.index)
                    cstWidth: rootId.width / 5 * 4
                    height: 1
                }
            }
        }


        ListView{
            anchors.fill: parent

            clip: true

            model: _wsModel

            delegate: Label {
                text: model.word + " : " + model.count
            }
        }

        ListView {
            id: lw

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10
            anchors.bottomMargin: 30

            //                        clip: true

            spacing: 10
            orientation: ListView.Horizontal
            interactive: false

            model: _wsModel

            property real widthCol: rootId.width / 5 * 4 / md.size()

            delegate: Rectangle {
                width: ((rootId.width / 5 * 4) - (_wsModel.rowCount() * 10 + 10)) / _wsModel.rowCount()
                y: lwBackId.height - (lwBackId.height / 100 * model.count)
                height: lwBackId.height / 100 * model.count - 10

                visible: model.index < 15

                border.width: 1

                //                color: "red"
                color: Qt.rgba(Math.random(), Math.random(), Math.random())

                Text{
                    height: 30
                    width: parent.width
                    text: model.count + ""

                    horizontalAlignment: Text.AlignHCenter
                }

                Text{
                    height: 30
                    width: parent.width
                    text: model.word
                    anchors.top: parent.bottom

                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

//        ListView {
//            id: lw

//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.left: parent.left
//            anchors.right: parent.right

//            anchors.margins: 10
//            anchors.bottomMargin: 30

//            //                        clip: true

//            spacing: 10
//            orientation: ListView.Horizontal
//            interactive: false

//            model: md.cpair

//            property real widthCol: rootId.width / 5 * 4 / md.size()

//            delegate: Rectangle {
//                width: ((rootId.width / 5 * 4) - (md.size() * 10 + 10)) / md.size()
//                y: lwBackId.height - (lwBackId.height / md.maxWord() * modelData.second)
//                height: lwBackId.height / md.maxWord() * modelData.second - 10

//                visible: model.index < 15

//                border.width: 1

////                color: "red"
//                color: Qt.rgba(Math.random(), Math.random(), Math.random())

//                Text{
//                    height: 30
//                    width: parent.width
//                    text: modelData.second

//                    horizontalAlignment: Text.AlignHCenter
//                }

//                Text{
//                    height: 30
//                    width: parent.width
//                    text: modelData.first
//                    anchors.top: parent.bottom

//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }
//        }
    }


    //    ChartView {
    //        title: "Гистограмма"

    //        anchors.fill: parent
    //        antialiasing: true
    //        legend.alignment: Qt.AlignBottom

    //        BarSeries {
    //            id:barseries

    //            axisX: BarCategoryAxis{
    ////                categories:["2007", "2008"]
    //                categories: md.name

    //                Component.onCompleted: {
    //                    console.log(md.cpair["first"], md.cpair["second"])
    //                }
    //            }

    //            BarSet {
    //                label: "Word";
    ////                values:[2,2]
    //                values: md.count
    //            }
    //            //            BarSet {label:"Susan";values:[2,1,2,4,1,7]}
    //            //            BarSet {label:"James";values:[2,5,8,13,5,8]}
    //        }
    //    }


}
