#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "android/log.h"

#include "opencv_tools.h"
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->text->setText("hello!");

    QImage img_qt(":/images/qt.png");
    if(img_qt.isNull())
        qErrnoWarning("Error loading image");

//    cv::Mat img_cv;
//    img_cv = qt2cv_shared(img_qt);
//    cv::imshow("img_cv", img_cv);
//    cv::waitKey(3);

//    img_qt = cv2qt_shared(img_cv);
    ui->label->setPixmap(QPixmap::fromImage(img_qt));
}
