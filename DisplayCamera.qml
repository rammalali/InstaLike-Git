import QtQuick 2.2
import QtQuick.Window 2.1
import QtMultimedia
import QtQuick.Controls 2.0
import QtQuick.Dialogs

Rectangle {
    id: dispCamId

    property url imageCap: imageCapture.preview
    property string imgCaption: ""

    width: windowId.width/1.2
    height: windowId.height/1.2
    color: "black"
    anchors.centerIn: parent

    // CAMERA DISPLAY
    MediaDevices {
        id: mediaDevices
    }
    CaptureSession {
        imageCapture : ImageCapture {
            id: imageCapture
        }

        camera: Camera {
            id: camera

            focusMode: Camera.FocusModeAutoNear
            customFocusPoint: Qt.point(0.2, 0.2) // Focus relative to top-left corner
            active: mediaDevices.defaultVideoInput
        }
        videoOutput: videoOutput
    }
    VideoOutput {
        id: videoOutput

        anchors.fill: parent
        visible: true

    }


    Button{
        id: captureBtnId
        anchors.top: dispCamId.bottom
        text: "Capture"
        anchors.left: dispCamId.left
        anchors.right: dispCamId.right
        onClicked: {
            videoOutput.visible = false
            imageCapture.capture()
            photoPreview.visible = true
            nextId.visible = true
            captureBtnId.visible = false
            retakeImgId.visible = true



        }
    }

    Image {
        id: photoPreview
        source: imageCap // always shows the last captured image
        anchors.centerIn: parent
        height: nextImgId.height
        width: photoPreview.height * 1.7


        visible: false
        Row{
            spacing: 2
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 15
            Button{
                id: retakeImgId
                text: "Retake Image"
                onClicked: {
                    photoPreview.visible = false
                    nextId.visible = false
                    retakeImgId.visible = false
                    videoOutput.visible = true
                    captureBtnId.visible = true
                }
            }
            Button{
                id: nextId
                text: "    Next    "
                visible: false
                onClicked: {

                    backBtn2Id.visible = true
                    dateOfCapture = Qt.formatDateTime(new Date(), "ddd yyyy-MM-dd hh:mm:ss")
                    console.log(dateOfCapture)
                    dispCamId.visible = false
                    nextImgId.visible = true
                    favBtnId.visible = true
                    filterBtnsId.visible = true
                }
            }
        }
    }

}
