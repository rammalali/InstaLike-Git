#include "filtergrayscale.h"
#include <QImage>
#include <opencv2/opencv.hpp>

FilterGrayscale::FilterGrayscale() :
Filter()
{
}
FilterGrayscale::~FilterGrayscale()
{
}

QImage FilterGrayscale::process(const QImage& image, int value)
{
// QImage => cv::mat
    cv::Mat tmp(image.height(),
                image.width(),
                CV_8UC4,
                (uchar*)image.bits(),
                image.bytesPerLine());
    cv::Mat resultMat;
    cv::cvtColor(tmp, resultMat, cv::COLOR_BGR2GRAY);
    // cv::mat => QImage
    QImage resultImage((const uchar *) resultMat.data,
                        resultMat.cols,
                        resultMat.rows,
                        resultMat.step,
                        QImage::Format_Grayscale8);
//    resultImage = resultImage.convertToFormat(QImage::Format_RGB32);

    return resultImage.copy();
}
