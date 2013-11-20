#ifndef VIDEOWIDGETSURFACE_H
#define VIDEOWIDGETSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>

class VideoCapture : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    VideoCapture(QObject *parent = 0);

    bool start(const QVideoSurfaceFormat &format);
    void stop();
    bool present(const QVideoFrame &frame);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    bool isFormatSupported(const QVideoSurfaceFormat &format) const;

private:
    QImage::Format imageFormat;
    QVideoFrame currentFrame;
};

#endif
