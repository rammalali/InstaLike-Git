
import QtCore 6.3
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import Qt.labs.folderlistmodel
import QtQuick.Dialogs
import ImageProcessor 1.0
import QtQuick.Layouts


ApplicationWindow {

    id: windowId
    visible: true
    width: 640
    height: 480
    minimumWidth: windowId.height * 1.7
    minimumHeight: 420
    property int heightProp: windowId.height
    property int widthProp: windowId.width

    property var imagesPath: imageProcessor.fileNames

    property url defPath: "file:///D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages"
    property url savePath: "file:///D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages"
    property url multiThreadingPath: ""
    property url imageCaptured: dispCamId.imageCap
    property url finalImg: imageProcessor.processImage
    property bool favoriteImgbool: false
    property url favoriteImg: "Images/favorite.png"
    property url notfavoriteImg: "Images/notFavorite.png"
    property url favorite: notfavoriteImg
    property string dateOfCapture: ""
    property bool usedFilter: false
    property bool favorite_return: false
    property double progressBarValue : 0
    property bool popUpfavorite: false



    property url favoriteUrl: "Images/notFavorite.png"


    function isItfavorite(){
        if(popUpfavorite === true){
            favoriteUrl = "qrc:/Images/favorite.png"
        }
        else if(popUpfavorite === false){
            favoriteUrl = "qrc:/Images/notFavorite.png"
        }
    }

    function getRandomInt(max) {
      return Math.floor(Math.random() * max);
    }

    function togglefavorite(){
        print("main.qml with value"+ favoriteImgbool)
        favoriteImgbool = ! favoriteImgbool
        favorite = favoriteImgbool ? favoriteImg : notfavoriteImg

    }

    Rectangle{
        id: menuBarRect
        height: menuBarId.height
        width: parent.width
        z:4
        color:"#eceaea"

    }

    MenuBar {
        id: menuBarId
        z:5
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Display Images")
                onTriggered: {
                    filtersColumn.visible = true
                    jayson.setSavefile(savePath)
                    imageProcessor.setFolderPath(defPath)
                    imagesPath= imageProcessor.fileNames
                    console.log(defPath)
                    dispCamId.visible= false
                    nextImgId.visible = false
                    favBtnId.visible = false
                    directoryImagesId.visible = true
                    scroller.visible = true
                    filterBtnsId.visible = false
                    backBtnId.visible = true
                    finalImageId.visible = false
                }

            }

            MenuSeparator { }
            Action { text: qsTr("&Quit"); onTriggered: Qt.quit() }
        }
    }
    Image{
        source: "Images/background.jpg"

        height: windowId.height
        width: windowId.width
        anchors.top: menuBarId.bottom
    }


    FileDialog {
        id: fileDialog

        nameFilters: [
                   "JSON files (*.json)",
               ]
        onAccepted: {
            console.log("User has selected " + fileDialog.currentFile);
            readTextFile(fileDialog.currentFile)
            flick.visible = true
            fileDialog.close()
        }
    }

    DisplayCamera{id: dispCamId }

    Image{
        id: nextImgId
        source: dispCamId.imageCap
        anchors.centerIn: parent
        anchors.top: menuBarId.bottom
        height: windowId.height/1.3
        width: nextImgId.height * 1.7
        visible: false
    }
    Row{
        id: filterBtnsId
        anchors.top: nextImgId.bottom
        anchors.horizontalCenter: nextImgId.horizontalCenter
        anchors.rightMargin: windowId.width/12
        anchors.bottom: windowId.bottom
        anchors.margins: windowId.height/30
        spacing: windowId.width/25

        visible: false
        TextField {
            id: imgTitleId
            height: windowId.height/20
            placeholderText: qsTr("Enter Image Title")


        }
        TextField {
            id: imgCaptionId
            height: windowId.height/20
            placeholderText: qsTr("Enter Image Caption")


        }

        Image{
            id: favBtnId
            source: favorite
            height: windowId.height/20
            width: favBtnId.height
            visible: false
            MouseArea{
                onClicked: togglefavorite()
                anchors.fill: parent
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.85
                                                : 1.0
            }

        }
        Column{
            Image{
                id: blurBtnId
                source: "Images/blur.png"
                height: windowId.height/19
                width: blurBtnId.height
                anchors.horizontalCenter: blurSliderId.horizontalCenter


                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        usedFilter = true
                        imageProcessor.setFilterType("Blur")
                        console.log(imageCaptured)
                        console.log(blurSliderId.value)
                        imageProcessor.setFilterValue(blurSliderId.value)
                        imageProcessor.setProcessImage(imageCaptured)
                        finalImageId.visible = true
                        nextImgId.visible = false
                        finalImg = imageProcessor.processImage
                        finalImageId.source = finalImg

                    }
                    hoverEnabled: true
                    onHoveredChanged: parent.opacity =
                                      containsMouse ? 0.7
                                                    : 1.0
                }
            }
            Slider {
                id: blurSliderId
                from: 2
                value: 3
                to: 30
            }
        }

        Image{
            id: grayBtnId
            source: "Images/grayScale.png"
            height: windowId.height/15
            width: grayBtnId.height
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    usedFilter = true
                    imageProcessor.setFilterType("Gray")
                    imageProcessor.setProcessImage(imageCaptured)
                    finalImageId.visible = true
                    nextImgId.visible = false
                    finalImg = imageProcessor.processImage
                    finalImageId.source = finalImg
                }
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.7
                                                : 1.0
            }
        }
        Image{
            id: originalBtnId
            source: "Images/original.png"
            height: windowId.height/15
            width: originalBtnId.height
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    usedFilter = true
                    imageProcessor.setFilterType("Original")
                    imageProcessor.setProcessImage(imageCaptured)
                    finalImageId.visible = true
                    nextImgId.visible = false
                    finalImg = imageProcessor.processImage
                    finalImageId.source = finalImg
                }
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.7
                                                : 1.0
            }
        }
        Image{
            id: saveBtnId
            source: "Images/floppy-disk.png"
            height: windowId.height/15
            width: originalBtnId.height
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(!usedFilter){
                        usedFilter = true
                        imageProcessor.setFilterType("Original")
                        imageProcessor.setProcessImage(imageCaptured)
                        finalImageId.visible = true
                        nextImgId.visible = false
                        finalImg = imageProcessor.processImage
                        finalImageId.source = finalImg
                }

                    jayson.setImgTitle(imgTitleId.text)
                    jayson.setImgCaption(imgCaptionId.text)
                    jayson.setCaptureDate(dateOfCapture)
                    jayson.setFavorite(favoriteImgbool)

                    jayson.setSavefile(savePath)
                    let id= getRandomInt(99999999)
                    jayson.setJson(id)

                    imageProcessor.qImageSave(savePath, id)
                }

            hoverEnabled: true
            onHoveredChanged: parent.opacity =
                              containsMouse ? 0.7
                                            : 1.0
            }
        }



        Image{
            id: backBtn2Id
            visible: false
            source: "Images/back.png"
            height: windowId.height/15
            width: backBtn2Id.height

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    dispCamId.visible = true
                    nextImgId.visible = false
                    filterBtnsId.visible = false
                    finalImageId.visible = false



                }
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.7
                                                : 1.0
            }
        }


    }
    Image{
        id: finalImageId
        height: nextImgId.height
        width: nextImgId.width
        visible: false
        smooth: true
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
//        source: finalImg

    }


    ScrollView {
        id: scroller
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.topMargin: 5
        width: parent.width
        height: parent.height
        clip : true
        visible: false

        GridLayout  {
            id: directoryImagesId
            visible: false
//            anchors.fill: parent
            anchors.right: filtersColumn.left
            columns: Math.max(Math.floor(windowId.width / 300), 1)

            columnSpacing: 5
            rowSpacing: 5
            Component.onCompleted: {
                console.log(Math.max(Math.floor(windowId.width / 300), 1))
            }

            Repeater{
                model: imagesPath

                Image {
                    id: imgtodisplay
                    Layout.preferredHeight: 146
                    Layout.preferredWidth: imgtodisplay.height*1.7
                    source: defPath +  "/" + modelData
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            popupId.src = defPath +  "/" + modelData
                            popupId.open()
                            jayson.setImgPath(defPath +  "/" + modelData)
                            favorite_return = jayson.favorite
                            popupId.imgTitle = jayson.imgTitle
                            popupId.imgCaption = jayson.imgCaption
                            popupId.dateofcap = jayson.captureDate
                            popUpfavorite = jayson.favorite
                            console.log(popUpfavorite)

                            isItfavorite()
                            console.log("favoriteurl: ", favoriteUrl)
                        }
                    }
                }
            }
        }

    }


    Column{
        id: filtersColumn
        visible: false
        y:heightProp/10
        x:widthProp/1.2
        spacing: heightProp/15
        Row{

            ProgressBar{
                id: progressBarId
                from: 0
                to: imagesPath.length

                Connections{
                    target: imageProcessor
                    function onProgressChanged(){
                        progressBarId.value = imageProcessor.progress;
                    }
                }
            }
        }

        // -----------------------------------------
        Image{
            id: applyToAllImg
            source: "Images/all1.png"
            height: windowId.height/3.5
            width: applyToAllImg.height/3
            anchors.horizontalCenter: filtersColumn.horizontalCenter
        }

        // -----------------------------------------

        Column{

            Image{
                id: multiThreadblurBtnId
                source: "Images/blur.png"
                height: windowId.height/19
                width: multiThreadblurBtnId.height
                anchors.horizontalCenter: multiThreadblurSliderId.horizontalCenter
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        imageProcessor.setFilterType("Blur")
                        imageProcessor.setFilterValue(multiThreadblurSliderId.value)

                        progressBarId.value = 0
                        imageProcessor.applyToall(defPath)

                    }
                    hoverEnabled: true
                    onHoveredChanged: parent.opacity =
                                      containsMouse ? 0.7
                                                    : 1.0
                }
            }
            Slider {
                    id: multiThreadblurSliderId
                    anchors.horizontalCenter: filtersColumn.horizontalCenter
                    from: 2
                    value: 3
                    to: 30
            }
        }

        Image{
            id: multiThreadgrayBtnId
            source: "Images/grayScale.png"
            height: windowId.height/15
            width: multiThreadgrayBtnId.height
            anchors.horizontalCenter: filtersColumn.horizontalCenter

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    imageProcessor.setFilterType("Gray")
                    progressBarId.value = 0
                    imageProcessor.applyToall(defPath)
                }
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.7
                                                : 1.0
            }
        }



    }
    Column{
        id: backBtnColumn
        y:heightProp/1.2
        x: filtersColumn.x + 25
        Image{
            id: backBtnId
            visible: false
            source: "Images/back.png"
            height: windowId.height/15
            width: backBtnId.height

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    filtersColumn.visible = false
                    directoryImagesId.visible= false
                    scroller.visible = false
                    dispCamId.visible= true
                    backBtnId.visible = false

                }
                hoverEnabled: true
                onHoveredChanged: parent.opacity =
                                  containsMouse ? 0.7
                                                : 1.0
            }
        }
    }


    PopUp{
        id: popupId
    }


    ImageProcessor{
        id: imageProcessor
    }



}
