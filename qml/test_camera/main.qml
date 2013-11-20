import QtQuick 2.1
import QtMultimedia 5.0

VideoOutput {
    source: camera

    Camera {
        id: camera
        objectName: "cameraObject"
    }
}
