import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Model 1.0

Window{
    id: rootId
    width: 640
    height: 480

    visible: true

    Md {
        id: md
    }

    Rectangle{
        id: lwBackId
        z: 1
        anchors.centerIn: parent

        width: parent.width / 5 * 4
        height: parent.height / 5 * 4 - 30

        border.width: 1

        property int tmpH: height / 5

        Column {
           width: parent.width
           height: parent.height

           Repeater {
               model: 5

               delegate: Seporator {
                   property real step: md.maxWord() / 5

                   y: lwBackId.tmpH * model.index + 10
//                   x: -5
                   sizeSep: md.maxWord() - (step * model.index)
//                   width: lwBackId.width
//                   height: 1
               }
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

            model: md.cpair

            property real widthCol: rootId.width / 5 * 4 / md.size()

            Component.onCompleted: {
                console.log(rootId.width / md.size(), rootId.width, md.size())
            }

            delegate: Rectangle {
                width: ((rootId.width / 5 * 4) - (md.size() * 10 + 10)) / md.size()
                y: lwBackId.height - (lwBackId.height / md.maxWord() * modelData.second)
                height: lwBackId.height / md.maxWord() * modelData.second - 10

                visible: model.index < 15

                border.width: 1

                color: "red"

                Text{
                    height: 30
                    width: parent.width
                    text: modelData.second
                }

                Text{
                    height: 30
                    width: parent.width
                    text: modelData.first
                    anchors.top: parent.bottom

                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
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
