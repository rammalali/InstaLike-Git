#include "filterblur.h"
#include <QImage>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QDebug>

FilterBlur::FilterBlur() :
Filter()
{
}
FilterBlur::~FilterBlur()
{
}

QImage FilterBlur::process(const QImage& image, int value)
{
//    if(value<3){
//        value=10;
//    }
//    qDebug() << image.format();
//    qDebug() << "start blur with value of" << value;
    // QImage => cv::mat

    cv::Mat tmp(image.height(),
                image.width(),
                CV_8UC4,
                (uchar*)image.bits(),
                image.bytesPerLine());
    int blur = value;
    cv::Mat resultMat;
    cv::GaussianBlur(tmp,
                    resultMat,
                    cv::Size(blur, blur),
                    0.0,
                    0.0);
    // cv::mat => QImage
    QImage resultImage((const uchar *) resultMat.data,
                        resultMat.cols,
                        resultMat.rows,
                        resultMat.step,
                        QImage::Format_RGB32);
//    qDebug() << "Blur done" << resultImage.copy();
    return resultImage.copy();
}
