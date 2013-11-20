#include "videocapture.h"

#include <qvideosurfaceformat.h>
#include <QDebug>

#include "opencv_tools.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

VideoCapture::VideoCapture(QObject *parent)
    : QAbstractVideoSurface(parent),
      imageFormat(QImage::Format_Invalid)
{
}

bool VideoCapture::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    if (imgFormat != QImage::Format_Invalid && !size.isEmpty())
    {
        imageFormat = imgFormat;
        QAbstractVideoSurface::start(format);
        return true;
    }

    return false;
}

void VideoCapture::stop()
{
    QAbstractVideoSurface::stop();
}

bool VideoCapture::present(const QVideoFrame &frame)
{
//    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
//            || surfaceFormat().frameSize() != frame.size())
//    {
//        setError(IncorrectFormatError);
//        stop();

//        return false;
//    }
//    else
//    {
        currentFrame = frame;

        if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
            QImage img( frame.bits(),
                        frame.width(),
                        frame.height(),
                        frame.bytesPerLine(),
                        imageFormat);


            // OpenCV example
            cv::Mat img_cv = qt2cv_shared(img);

            // Gray scale
            cv::Mat src_gray, detected_edges;
            cvtColor(img_cv, src_gray, CV_BGR2GRAY);

            // Reduce noise with a kernel 3x3
            cv::blur(src_gray, detected_edges, cv::Size(3,3));

            // Canny detector
            int ratio = 3;
            int kernel_size = 3;
            int threshold = 30;
            cv::Canny(detected_edges, detected_edges, threshold, threshold*ratio, kernel_size);

            cv::imshow("detected_edges", detected_edges);
            cv::waitKey(3);

            // Get Qt Image
            // QImage dst = cv2qt_shared(detected_edges);

//            currentFrame.unmap(); // do we need this?
        }

        return true;
//    }
}

QList<QVideoFrame::PixelFormat> VideoCapture::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
                    << QVideoFrame::Format_RGB32
                    << QVideoFrame::Format_ARGB32
                    << QVideoFrame::Format_ARGB32_Premultiplied
                    << QVideoFrame::Format_RGB565
                    << QVideoFrame::Format_RGB555;
    }

    return QList<QVideoFrame::PixelFormat>();
}

bool VideoCapture::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
                && !size.isEmpty()
                && format.handleType() == QAbstractVideoBuffer::NoHandle;
}
