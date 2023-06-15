#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::DisplayImage(){

    QImage imdisplay((uchar*)m_toDisplayImg.data, m_toDisplayImg.cols, m_toDisplayImg.rows, m_toDisplayImg.step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    ui->imageDisplay->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier
}

void MainWindow::DisplayVideo(){

    VideoCapture vidCapture(m_vidFileName.toStdString());

    while (vidCapture.isOpened()){
        Mat frame;
        if (vidCapture.read(frame)){
            QImage imdisplay((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
            ui->videoDisplay->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier
        } else
            return;
        int key = waitKey(20);
        if (key == 'q')
            break;
    }
    vidCapture.release();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openImage_clicked()
{
    m_imgFileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));

    m_sourceImg = imread(m_imgFileName.toStdString());
    cv::resize(m_sourceImg, m_sourceImg, Size(512, 384), 0, 0, INTER_LINEAR);
    cv::cvtColor(m_sourceImg, m_sourceImg,COLOR_BGR2RGB); //Qt reads in RGB whereas CV in BGR
    m_toDisplayImg = m_sourceImg.clone();

    DisplayImage();
}

void MainWindow::on_noFilter_clicked()
{
    if (m_sourceImg.empty())
        return;

    m_toDisplayImg = m_sourceImg.clone();

    DisplayImage();
}

void MainWindow::on_filter1_clicked()
{
    if (m_sourceImg.empty())
        return;

    Mat kernel1 = Mat::ones(5 , 5, CV_64F);
    kernel1 = kernel1 / 25;

    filter2D(m_sourceImg, m_toDisplayImg, -1, kernel1, Point(-1, -1), 0, 4);

    DisplayImage();
}

void MainWindow::on_filter2_clicked()
{
    if (m_sourceImg.empty())
        return;

    GaussianBlur(m_sourceImg, m_toDisplayImg, Size(5, 5), 0, 0);

    DisplayImage();
}

void MainWindow::on_filter3_clicked()
{
    if (m_sourceImg.empty())
        return;

    Mat kernel3 = (Mat_<double>(3,3) << 0, -1,  0,
                                       -1,  5, -1,
                                        0, -1, 0);

    filter2D(m_sourceImg, m_toDisplayImg, -1 , kernel3, Point(-1, -1), 0, BORDER_DEFAULT);

    DisplayImage();
}

void MainWindow::on_openVideo_clicked()
{
    m_vidFileName = QFileDialog::getOpenFileName(this, tr("Open Video"), QDir::currentPath(), tr("Video Files (*.mp4 *.avi)"));

    DisplayVideo();
}

