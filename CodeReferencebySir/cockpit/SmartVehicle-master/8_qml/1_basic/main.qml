import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1040
    height: 780
    title: qsTr("Hello World")

    id:root
    color:"#FF0909";
    property int rotationStep: 45
    BorderImage {
        source: "images/Cluster1.png"
    }
    AnimatedImage {
        id: emgr
        source: "images/emg.gif"
        width:100
        height:100
        x:600
        y:10
    }
    Rectangle
    {

        property int frames: emgr.frameCount
        width:(emgr.width-width) * emgr.currentFrame / frames;
        height:emgr.height
        x:600
        y:100
        color: "blue"

        Text{
            id: timertb
            text: emgr.currentFrame
            color: "black"
            font.family: "Helvetica"
            font.pixelSize: 32
            anchors.top: parent.bottom
            anchors.centerIn: parent
        }
    }
    Image {
            id: icon1
            anchors.horizontalCenter:  parent.horizontalCenter
            anchors.bottom: parent.bottom
            source: "images/icon1.png"
    }

    Image {
            id: icon2
            anchors.centerIn: parent
            source: "images/icon2.png"

            Behavior on rotation {
                    NumberAnimation {
                        duration: 250
                    }
            }
    }

    MouseArea {
            anchors.fill: parent
            onPressed: {
                icon2.rotation += 90
            }
            onClicked: {
                if(emgr.paused == true)
                {
                    emgr.paused = false;
                }
                else
                {
                    emgr.paused = true;
                    timertb.text = "emgr.currentFrame"
                }
            }
    }

    Item{
        anchors.fill: parent
        focus: true
        Keys.onLeftPressed: {
            console.log("move left");
            icon1.rotation -= root.rotationStep
        }

        Keys.onRightPressed: {
            console.log("move right")
            icon1.rotation += root.rotationStep
        }
    }
}
