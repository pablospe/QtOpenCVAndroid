import QtQuick 2.0
import QtMultimedia 5.0
import QtQuick 2.1

VideoOutput {
    width: 600
    height: 480
    source: camera

    Camera {
        id: camera
        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
        captureMode: Camera.CaptureStillImage

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait
        }
    }
}
