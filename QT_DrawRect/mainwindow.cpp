#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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
    Mat srcImage = imread("/home/mark/Sofeware/Qt/Qt_Project/QtApplication2/QT_DrawRect/lena.png");
    Mat tempImage = srcImage;
    cvtColor(tempImage, tempImage, CV_BGR2RGB);
    QImage image((const uchar*)tempImage.data, tempImage.cols, tempImage.rows,
                     tempImage.cols*tempImage.channels(), QImage::Format_RGB888);
    QImage showImage = image.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(showImage));
}

void MainWindow::on_pushButton_2_clicked()
{
    int start_h = 220, start_w = 180;
    int rectSize = 50, scaleSize=3;
    Rect rect1 = Rect(start_h, start_w, rectSize, rectSize);        // specific rect
    Mat srcImage = imread("/home/mark/Sofeware/Qt/Qt_Project/QtApplication2/QT_DrawRect/lena.png");
    Mat imageRect = srcImage;
    cvtColor(imageRect, imageRect, CV_BGR2RGB);     // convert the BGR image to RGB
    Mat image_ROI = imageRect(rect1);    // define the ROI area and magnification ROI area
    Mat image_scaleROI;
    cv::resize(image_ROI, image_scaleROI, Size(scaleSize*rectSize, scaleSize*rectSize));
    Rect rect2 = Rect(imageRect.rows-image_scaleROI.rows, imageRect.cols-image_scaleROI.cols,  // magnification rect
                      image_scaleROI.rows, image_scaleROI.cols);
    image_scaleROI.copyTo(imageRect(rect2));        // cover the scaled ROI area
    rectangle(imageRect,rect1,cvScalar(255,0,0),2);  // draw two rect
    rectangle(imageRect,rect2,cvScalar(255,0,0),2);
    QImage image((const uchar*)imageRect.data, imageRect.cols, imageRect.rows,       // show image in Qlabel
                     imageRect.cols*imageRect.channels(), QImage::Format_RGB888);
    QImage showImage = image.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(showImage));
    cvtColor(imageRect, imageRect, CV_RGB2BGR);
    imwrite("/home/mark/Sofeware/Qt/Qt_Project/QtApplication2/QT_DrawRect/output.png", imageRect);
}
