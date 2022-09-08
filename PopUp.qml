import QtQuick 2.2
import QtQuick.Controls 2.12

Popup{
    id: popupId
    height: windowId.height/1.1
    width: popupId.height * 1.7
    visible: false
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    anchors.centerIn: parent
    property url src: ""
    property string imgTitle: ""
    property string imgCaption: ""
    property string dateofcap: ""
    property int popUpfontsize: 10

    Component.onCompleted: {
        isItfavorite()
        console.log(favoriteUrl)
    }

    Rectangle{
        anchors.centerIn: parent
        Image{
            id: popupImg
            smooth: true
            height: windowId.height/1.3
            width: popupImg.height * 1.7
            anchors.centerIn: parent
            source: src
        }

        Row{
            id: informations
            spacing: 5
            anchors.top: popupImg.bottom
            anchors.left: popupImg.left
            anchors.leftMargin: 30

            Text {

                text: "Title: " + imgTitle
                font.family: "Corbel"
                font.pointSize: popUpfontsize
            }

            Text{
                text: " | "
                font.pointSize: popUpfontsize

            }

            Text {

                text: "Caption: " + imgCaption
                font.family: "Corbel"
                font.pointSize: popUpfontsize
            }
            Text{
                text: " | "
                font.pointSize: popUpfontsize

            }
            Text {

                text: "Date Of Capture: " + dateofcap
                font.family: "Corbel"
                font.pointSize: popUpfontsize
            }
            Text{
                text: " | "
                font.pointSize: popUpfontsize

            }
            Image {
                source: favoriteUrl
                height: 20
                width: 20
            }
        }
    }



}

