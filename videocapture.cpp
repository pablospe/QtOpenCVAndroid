#include "videocapture.h"

#include <qvideosurfaceformat.h>
#include <QDebug>

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

            qDebug() << "img.width() " << img.width();
            mLabel->setPixmap(QPixmap::fromImage(img));

            currentFrame.unmap();
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
