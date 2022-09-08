#include "qbuffer.h"
#include <imageprocessor.h>
#include <Filters/filterblur.h>
#include <Filters/filtergrayscale.h>
#include <Filters/filteroriginal.h>

#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QDebug>
#include <iostream>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <string>
#include <QRandomGenerator>
#include <QDir>
#include <jsonates.h>

using namespace std;
ImageProcessor::ImageProcessor(QObject *parent)
    : QThread(parent)
{}

const QString &ImageProcessor::processImage()
{
      // Some init code to setup the image (e.g. loading a PGN/JPEG, etc.)
    if(!QDir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages").exists()){
//        qDebug() << QDir().currentPath() << "dirrrrrrrrrrrrrrrrrrrrr";
        QDir().mkdir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages");
    }


    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    m_processImage.save(&buffer, "JPEG");

    m_Image = "data:image/jpg;base64,";
    m_Image.append(QString::fromLatin1(bArray.toBase64().data()));

    return m_Image;
}

void ImageProcessor::setProcessImage( const QString& path)
{
    if(!QDir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages").exists()){
//        qDebug() << QDir().currentPath() << "dirrrrrrrrrrrrrrrrrrrrr";
        QDir().mkdir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages");
    }
    qDebug() << "Set Process Image Start -->";

    QUrl imageUrl(path);

    QQmlEngine* engine = QQmlEngine::contextForObject(this)->engine();


    QQmlImageProviderBase* imageProviderBase = engine->imageProvider(imageUrl.host());
    QQuickImageProvider* imageProvider = static_cast<QQuickImageProvider*>(imageProviderBase);

    QImage newProcessImage;

    QSize imageSize;
    QString imageId = imageUrl.path().remove(0,1);
    qDebug() << imageUrl.path().remove(0, imageUrl.path().length() - 3);
    if(imageUrl.path().remove(0, imageUrl.path().length() - 3) != "png" && imageUrl.path().remove(0, imageUrl.path().length() - 3) != "jpg"){
        newProcessImage = imageProvider->requestImage(imageId, &imageSize, imageSize);
    }
    else
        newProcessImage.load(path);

    qDebug() << "before if : ";
    if(newProcessImage.format() == QImage::Format_RGB32){
        if( !newProcessImage.isNull()) {
            if(m_filterType == "Blur"){

                FilterBlur blur;
                m_processImage = blur.process(newProcessImage, m_value);

            }
            if(m_filterType == "Gray"){

                FilterGrayscale gray;
                m_processImage = gray.process(newProcessImage, 1);
                m_processImage = m_processImage.convertToFormat(QImage::Format_RGB32);

            }
            if(m_filterType == "Original"){

                FilterOriginal original;
                m_processImage = original.process(newProcessImage, 1);
            }

        }
        if (m_processImage == newProcessImage)

            return;
    }


}



void ImageProcessor::setFilterType(QString filterType){
    m_filterType = filterType;
}

void ImageProcessor::setFilterValue(float NewValue)
{
    m_value = (int)NewValue;
    if(m_value%2 == 0){
        m_value += 1;
    }
}

void ImageProcessor::qImageSave(QString m_savePath, QString id)
{
    if(!QDir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages").exists()){
//        qDebug() << QDir().currentPath() << "dirrrrrrrrrrrrrrrrrrrrr";
        QDir().mkdir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages");
    }
    if(m_savePath == ""){
        m_savePath = QDir::homePath() + "/Pictures";
        if (QDir(m_savePath + "/Qt").exists()){
            m_savePath = m_savePath + "/Qt";
        }
        else{
            QDir().mkdir(m_savePath + "/Qt");
            m_savePath = m_savePath + "/Qt";
        }

    }
    m_savePath.remove("file:///");
    QString path  = m_savePath + "/" + id + ".jpg";

    m_processImage.save(path, "jpg");
}


const QStringList &ImageProcessor::fileNames() const
{
    return m_fileNames;
}

void ImageProcessor::setFolderPath(QString path){

    path.remove("file:///");
    m_folderPath = path;

    m_fileNames = m_folderPath.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);

}

float ImageProcessor::progress() const
{
    return m_progress;
}

void ImageProcessor::setProgress(float newProgress)
{
    qDebug() << newProgress;
    if (qFuzzyCompare(m_progress, newProgress))
        return;
    m_progress = newProgress;
    emit progressChanged();
}

void ImageProcessor::run()
{
    FilterGrayscale gray;
    FilterBlur blur;

    QString m_savename;

    if(!QDir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages").exists()){
//        qDebug() << QDir().currentPath() << "dirrrrrrrrrrrrrrrrrrrrr";
        QDir().mkdir("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages");
    }
    for(int i = 0;i < m_fileNames.size(); i++){
        qDebug() << "filename: " << m_fileNames[i];
        m_savename = m_fileNames[i].mid(0, m_fileNames[i].indexOf(".")) ;


        QImage imgToProcess("D:/uni/Internships/Cme-1er/Qt/Projects/InstaLike/InstaLikeImages" + m_fileNames[i]);
        qDebug() << imgToProcess;


        qDebug() << "before if : ";

        if( !imgToProcess.isNull()) {
            if(m_filterType == "Blur"){

                m_processImage = blur.process(imgToProcess, m_value);

            }
            if(m_filterType == "Gray"){

                qDebug() << "Going to Gray >>>";

                m_processImage = gray.process(imgToProcess, 1);
                qDebug() << "after process";
                if(m_processImage.format() != QImage::Format_RGB32){
                    m_processImage = m_processImage.convertToFormat(QImage::Format_RGB32);
                }
            }
            if(m_filterType == "Original"){
                FilterOriginal original;
                m_processImage = original.process(imgToProcess, 1);
            }

        }

        qDebug() << m_savename;
        qImageSave(m_saveDirectory, m_savename);
        setProgress(i+1);

        emit progressChanged();
    }
}

void ImageProcessor::applyToall( QString saveDirectory){
    m_saveDirectory = saveDirectory;
    ImageProcessor::start();

}
